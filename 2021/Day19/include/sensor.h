#include <optional>
#include <vector>
#include <memory>
#include <unordered_map>
#include <grid.h>

struct dimGridVecHash
{
  std::size_t operator() (const DimensionGrid<3>::Vec& vec) const
  {
    std::size_t seed = vec.deltas.size();
    for (auto& i : vec.deltas) 
    {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

struct SensorData 
{
  SensorData() = default;

  explicit SensorData(std::vector<DimensionGrid<3>::Vec> beacon_signals) : beacon_signals_(std::move(beacon_signals)) {}

  SensorData(const SensorData& other) : position_(other.position_), beacon_signals_(other.beacon_signals_) {}
  SensorData(SensorData&& other) : position_(std::move(other.position_)),
    beacon_signals_(std::move(other.beacon_signals_)),
    all_orientations_(std::move(other.all_orientations_)) {}

  SensorData& operator=(const SensorData& other) 
  {
    if (&other == this) 
      return *this;

    position_ = other.position_;
    beacon_signals_ = other.beacon_signals_;
    all_orientations_.reset();
    return *this;
  }

  SensorData& operator=(SensorData&& other) 
  {
    if (&other == this) 
      return *this;

    position_ = std::move(other.position_);
    beacon_signals_ = std::move(other.beacon_signals_);
    all_orientations_ = std::move(other.all_orientations_);
    return *this;
  }

  void SetPosition(DimensionGrid<3>::Point position) 
  {
    position_ = std::move(position);
  }

  bool esta(std::vector < DimensionGrid<3>::Vec>& vecAux, DimensionGrid<3>::Vec aux)
  {
    bool ok = false;
    for (auto& v : vecAux)
      if (v.deltas[0] == aux.deltas[0] && v.deltas[1] == aux.deltas[1] && v.deltas[2] == aux.deltas[2])
        return true;

    return false;
  }

  bool MatchToKnown(const SensorData& known) 
  { 
    for (const auto& candidate_orientation : AllOrientations()) 
    {
      std::unordered_map<DimensionGrid<3>::Vec, int, dimGridVecHash> offset_counts;
      for (const auto& outer_signal : known.beacon_signals_) 
      {
        for (const auto& inner_signal : candidate_orientation) 
        {
          ++offset_counts[outer_signal - inner_signal];
        }
      }

      for (auto& [offset, count] : offset_counts) 
      {
        if (count >= 12) 
        {
          position_ = known.position_.value() + offset;
          beacon_signals_ = candidate_orientation;
          return true;
        }
      }
    }

    return false;
  }

  DimensionGrid<3>::Point position() const 
  {
    return *position_;
  }

  std::vector<DimensionGrid<3>::Point> AbsoluteBeaconPositions() const 
  {
    return *position_ + beacon_signals_;
  }

private:
  const std::vector<std::vector<DimensionGrid<3>::Vec>>& AllOrientations() 
  {
    if (all_orientations_ != nullptr) 
      return *all_orientations_;

    all_orientations_ = std::make_unique<std::vector<std::vector<DimensionGrid<3>::Vec>>>();
    for (const auto& rot : DimensionGrid<3>::Rotations::AllOrientations()) 
    {
      all_orientations_->emplace_back(beacon_signals_ * rot);
    }

    return *all_orientations_;
  }

  std::optional<DimensionGrid<3>::Point> position_;
  std::vector<DimensionGrid<3>::Vec> beacon_signals_;
  std::unique_ptr<std::vector<std::vector<DimensionGrid<3>::Vec>>> all_orientations_;
};
