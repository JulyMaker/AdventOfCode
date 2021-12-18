#include <variant>
#include <memory>
#include <string>
#include <iostream>

class Number 
{
public:
  static std::unique_ptr<Number> parse(std::string rep, Number* parent = nullptr) 
  {
    auto num = std::make_unique<Number>();
    num->parent_ = parent;

    int depth = 0;
    int comma = -1;
    for (int pos = 0; pos < rep.size(); ++pos) 
    {
      switch (rep[pos]) 
      {
        case '[':
          ++depth;
          break;
        case ']':
          --depth;
          break;
        case ',':
          if (depth == 1) 
          {
            comma = pos;
          }
          break;
      }
    }

    std::string left_rep = rep.substr(1, comma - 1);
    std::string right_rep = rep.substr(comma + 1, rep.size()-1);

    //if (inputLine.at(0) == '%')
    //int burnRate = stoi(inputLine);

    try 
    {
      int left_int = std::stoi(left_rep);
      num->left_ = left_int;
    }
    catch (std::invalid_argument const& ex) 
    {
      num->left_ = parse(left_rep, num.get());
    }
    
    try 
    {
      int right_int = std::stoi(right_rep);
      num->right_ = right_int;
    }
    catch (std::invalid_argument const& ex) 
    {
      num->right_ = parse(right_rep, num.get());
    }

    return num;
  }

  static std::unique_ptr<Number> add(std::unique_ptr<Number> left, std::unique_ptr<Number> right) 
  {
    auto num = std::make_unique<Number>();
    left->parent_ = num.get();
    right->parent_ = num.get();
    num->left_ = std::move(left);
    num->right_ = std::move(right);
    return num;
  }

  void reduce() 
  {
    for (;;) 
    {
      if (maybeExplode(1)) continue;
      if (maybeSplit()) continue;
      return;
    }
  }

  int magnitude() const 
  {
    int mag = 0;
    if (left_.index() == 0) 
    {
      mag += 3 * std::get<0>(left_);
    }
    else 
    {
      mag += 3 * std::get<1>(left_)->magnitude();
    }

    if (right_.index() == 0) {
      mag += 2 * std::get<0>(right_);
    }
    else 
    {
      mag += 2 * std::get<1>(right_)->magnitude();
    }

    return mag;
  }

  void DebugPrint() const 
  {
    std::cout << "[";
    if (left_.index() == 0) 
    {
      std::cout << std::get<0>(left_);
    }
    else 
    {
      std::get<1>(left_)->DebugPrint();
    }

    std::cout << ",";
    if (right_.index() == 0) 
    {
      std::cout << std::get<0>(right_);
    }
    else 
    {
      std::get<1>(right_)->DebugPrint();
    }

    std::cout << "]";
  }

private:
  int explode() const 
  {
    int* left_of_pair = findLeft();
    if (left_of_pair != nullptr) 
      *left_of_pair += std::get<0>(left_);

    int* right_of_pair = findRight();
    if (right_of_pair != nullptr) 
      *right_of_pair += std::get<0>(right_);

    return 0;
  }

  std::unique_ptr<Number> split(int value) 
  {
    auto num = std::make_unique<Number>();
    num->parent_ = this;
    num->left_ = static_cast<int>(std::floor(static_cast<double>(value) / 2.0));
    num->right_ = static_cast<int>(std::ceil(static_cast<double>(value) / 2.0));
    return num;
  }

  bool maybeExplode(int depth) 
  {
    if (depth == 4) 
    {
      if (left_.index() == 1) 
      {
        left_ = std::get<1>(left_)->explode();
        return true;
      }

      if (right_.index() == 1) 
      {
        right_ = std::get<1>(right_)->explode();
        return true;
      }
    }

    if (left_.index() == 1 && std::get<1>(left_)->maybeExplode(depth + 1))
      return true;
    if (right_.index() == 1 && std::get<1>(right_)->maybeExplode(depth + 1))
      return true;
    return false;
  }

  bool maybeSplit() 
  {
    if (left_.index() == 0 && std::get<0>(left_) >= 10) 
    {
      left_ = split(std::get<0>(left_));
      return true;
    }
    if (left_.index() == 1 && std::get<1>(left_)->maybeSplit()) 
      return true;

    if (right_.index() == 0 && std::get<0>(right_) >= 10) 
    {
      right_ = split(std::get<0>(right_));
      return true;
    }
    if (right_.index() == 1 && std::get<1>(right_)->maybeSplit()) 
      return true;

    return false;
  }

  int* leftMost() 
  {
    if (left_.index() == 0) 
      return &std::get<0>(left_);

    return std::get<1>(left_)->leftMost();
  }

  int* rightMost() 
  {
    if (right_.index() == 0)
      return &std::get<0>(right_);

    return std::get<1>(right_)->rightMost();
  }

  int* findLeft() const 
  {
    if (parent_ == nullptr)
      return nullptr;

    if (parent_->left_.index() == 1 && std::get<1>(parent_->left_).get() == this) 
    {
      return parent_->findLeft();
    }

    if (parent_->left_.index() == 0) 
      return &std::get<0>(parent_->left_);

    return std::get<1>(parent_->left_)->rightMost();
  }

  int* findRight() const 
  {
    if (parent_ == nullptr) 
      return nullptr;

    if (parent_->right_.index() == 1 && std::get<1>(parent_->right_).get() == this) 
    {
      return parent_->findRight();
    }

    if (parent_->right_.index() == 0) 
      return &std::get<0>(parent_->right_);

    return std::get<1>(parent_->right_)->leftMost();
  }

  Number* parent_ = nullptr;
  std::variant<int, std::unique_ptr<Number>> left_;
  std::variant<int, std::unique_ptr<Number>> right_;
};
