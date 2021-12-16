#include <variant>
#include <vector>
#include <memory>

struct Packet
{
  uint8_t version_ = 0;
  uint8_t type_ = 0;

  std::variant<uint64_t, std::vector<std::unique_ptr<Packet>>> contents_;

  uint64_t addVersions() const
  {
    uint64_t sum = version_;
    if (std::holds_alternative<std::vector<std::unique_ptr<Packet>>>(contents_))
    {
      for (const std::unique_ptr<Packet>& subpacket : std::get<std::vector<std::unique_ptr<Packet>>>(contents_))
      {
        sum += subpacket->addVersions();
      }
    }
    return sum;
  }

  uint64_t calculateValue() const
  {
    switch (type_)
    {
      case 0:
      {
        uint64_t sum = 0;
        for (const auto& subpacket : std::get<1>(contents_))
          sum += subpacket->calculateValue();
            
        return sum;
      }
      case 1:
      {
        uint64_t product = 1;
        for (const auto& subpacket : std::get<1>(contents_))
          product *= subpacket->calculateValue();
      
        return product;
      }
      case 2:
      {
        uint64_t min = std::numeric_limits<uint64_t>::max();
        for (const auto& subpacket : std::get<1>(contents_))
          min = std::min(min, subpacket->calculateValue());
      
        return min;
      }
      case 3:
      {
        uint64_t max = std::numeric_limits<uint64_t>::min();
        for (const auto& subpacket : std::get<1>(contents_))
          max = std::max(max, subpacket->calculateValue());
      
        return max;
      }
      case 4:
        return std::get<0>(contents_);
      case 5:
        return (std::get<1>(contents_).front()->calculateValue() > std::get<1>(contents_).back()->calculateValue()) ? 1 : 0;
      case 6:
        return (std::get<1>(contents_).front()->calculateValue() < std::get<1>(contents_).back()->calculateValue()) ? 1 : 0;
      case 7:
        return (std::get<1>(contents_).front()->calculateValue() == std::get<1>(contents_).back()->calculateValue()) ? 1 : 0;
    }
  }
};

struct PacketAndIterator
{
  std::unique_ptr<Packet> packet;
  std::vector<bool>::const_iterator after;
};