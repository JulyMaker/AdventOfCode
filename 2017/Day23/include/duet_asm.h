#ifndef DUET_ASM_H
#define DUET_ASM_H

#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>
#include <queue>

template <typename T>
struct safe_queue {

  template <typename U>
  void enqueue(U && u) {
    std::lock_guard lock{ m };
    q.push(std::forward<U>(u));
    c.notify_one();
  }

  T dequeue() {
    std::unique_lock lock{ m };
    c.wait(lock, [&] { return !q.empty(); });
    T val = q.front();
    q.pop();
    return val;
  }

  bool empty() const {
    return q.empty();
  }

private:
  std::queue<T> q;
  mutable std::mutex m;
  std::condition_variable c;
};

constexpr uint64_t
hash(const char* str, uint64_t ret = 0x0ull)
{
  return (*str) ? hash(str + 1, (ret << 8) | *(str + 1)) : ret;
}

constexpr uint64_t
hash(const std::string& str)
{
  return hash(str.c_str());
}

constexpr uint64_t operator"" _hash(const char* p, size_t)
{
  return hash(p);
}

struct program 
{

  struct instr 
  {
    using arg = std::variant<long, char>;
    std::string cmd;
    arg         arg1, arg2;
  };

  program(std::vector<instr> const& lst, long val = 0): lst(lst) 
  {
    reg['p' - 'a'] = val;
  }

  void run(program* p) 
  {
    while (true) 
    {
      auto[done, _] = apply(p);
      if (done)
        return;
    }
  }

  bool deadlock() const 
  {
    return lst[ip].cmd == "rcv" && buf.empty();
  }

  int send_count() const 
  {
    return sends;
  }

  inline program::instr const & curr() const 
  {
    program::instr ins;
    if (ip >= lst.size())
      return ins;
    else
      return lst[ip];
  }

  inline std::pair<bool, std::optional<long>> apply(program* other = nullptr) 
  {
    int next = 1;
    std::optional<long> ret;

    if (ip >= lst.size())
      return {true, ret};
    
    auto const &cmd = lst[ip].cmd;
    auto const &a1 = lst[ip].arg1;
    auto const &a2 = lst[ip].arg2;

    switch (hash(cmd)) 
    {
      case "set"_hash: at(a1)  = value_of(a2); break;
      case "add"_hash: at(a1) += value_of(a2); break;
      case "sub"_hash: at(a1) -= value_of(a2); break;
      case "mul"_hash: at(a1) *= value_of(a2); break;
      case "mod"_hash: at(a1) %= value_of(a2); break;
      case "sqrt"_hash:
        at(a1) = std::ceil(std::sqrt(value_of(a2)));
        //std::cerr << "g: " << at(a1) << ' ' << "d: " << value('d') << '\n';
        break;
      case "snd"_hash:
        ++sends;
        if (other)
          other->buf.enqueue(value_of(a1));
        else
          last = value_of(a1);
        break;
      case "rcv"_hash:
        if (other)
          at(a1) = buf.dequeue();
        else if (value_of(a1) != 0)
          ret = last;
        break;
      case "jgz"_hash:
        if (value_of(a1) > 0)
          next = value_of(a2);
        break;
      case "jlz"_hash:
        if (value_of(a1) < 0)
          next = value_of(a2);
        break;
      case "jnz"_hash:
        if (value_of(a1) != 0)
          next = value_of(a2);
        break;
      case "jge"_hash:
        if (value_of(a1) <= 0)
          next = value_of(a2);
        break;
      case "jle"_hash:
        if (value_of(a1) <= 0)
          next = value_of(a2);
        break;
    }
    ip += next;
    return {ip >= lst.size(), ret};
  }

  inline long value(char r) const 
  {
    return reg[r - 'a'];
  }

  inline void set(char r, long v) 
  {
    reg[r - 'a'] = v;
  }

  private:

  long long& at(instr::arg const& a) 
  {
    return reg[std::get<char>(a) - 'a'];
  }

  long value_of(instr::arg const& a) const 
  {
    if (std::holds_alternative<long>(a))
      return std::get<long>(a);
    if (std::get<char>(a) - 'a' < 0)
      return 0;

    return reg[std::get<char>(a) - 'a'];
  }

  std::vector<instr> const& lst;
  std::array<long long, 26> reg{{0}};
  safe_queue<long> buf;
  std::optional<long> last;
  unsigned int ip=0, sends=0;
};

inline std::istream& operator>>(std::istream& is, program::instr::arg& v) 
{
  if (is.peek() == ' ')
    is.ignore(1);
  if (char c; std::isalpha(is.peek())) {
    is >> c; v = c;
  } else if (long val; std::isdigit(is.peek()) || is.peek() == '-') {
    is >> val; v = val;
  }
  return is;
}

inline std::istream& operator>>(std::istream& is, program::instr& i) 
{
  if (is.peek() == '\n')
    is.ignore(1);
  is >> i.cmd >> i.arg1 >> i.arg2;
  return is;
}

inline std::ostream& operator<<(std::ostream& os, program::instr::arg const & a) 
{
  if (std::holds_alternative<long>(a)) 
  {
    return os << std::get<long>(a);
  } else if (std::holds_alternative<char>(a)) 
  {
    return os << std::get<char>(a);
  } else 
  {
    return os;
  }
}

inline std::ostream& operator<<(std::ostream& os, program::instr const & i) 
{
  os << '[' << i.cmd << ' ' << i.arg1 << ' ' << i.arg2 << ']';
  return os;
}
#endif