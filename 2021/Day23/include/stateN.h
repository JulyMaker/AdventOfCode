#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

constexpr int kRoomSize = 4;

enum class CellN : char { kEmpty = 0, kA, kB, kC, kD };

CellN ParseCell(const char c) 
{
  switch (c) 
  {
    case '.':
      return CellN::kEmpty;
    case 'A':
      return CellN::kA;
    case 'B':
      return CellN::kB;
    case 'C':
      return CellN::kC;
    case 'D':
      return CellN::kD;
    default:
      std::exit(1);
  }
}

int RoomPosition(const CellN cell) 
{
  switch (cell) 
  {
    case CellN::kEmpty:
      std::exit(1);
    case CellN::kA:
      return 2;
    case CellN::kB:
      return 4;
    case CellN::kC:
      return 6;
    case CellN::kD:
      return 8;
  }
}

int64_t Energy(const CellN cell) 
{
  switch (cell) 
  {
    case CellN::kEmpty:
      std::exit(1);
    case CellN::kA:
      return 1;
    case CellN::kB:
      return 10;
    case CellN::kC:
      return 100;
    case CellN::kD:
      return 1000;
  }
}

struct StateN
{
  std::array<CellN, 11> hallway;
  std::array<CellN, kRoomSize> room_a;
  std::array<CellN, kRoomSize> room_b;
  std::array<CellN, kRoomSize> room_c;
  std::array<CellN, kRoomSize> room_d;

  std::vector<std::pair<StateN, int64_t>> SuccessorStates() const
  {
    std::vector<std::pair<StateN, int64_t>> successors;

    // Moving Amphipods -> Final Rooms.
    for (int hallway_pos = 0; hallway_pos < 11; ++hallway_pos) 
    {
      const CellN source_cell = hallway[hallway_pos];
      if (source_cell == CellN::kEmpty) 
        continue;

      int destination = RoomPosition(source_cell);
      bool path_clear = true;
      if (hallway_pos < destination) 
      {
        for (int pos = hallway_pos + 1; pos <= destination; ++pos) 
        {
          if (hallway[pos] != CellN::kEmpty) 
          {
            path_clear = false;
            break;
          }
        }
      }
      else 
      {  
        for (int pos = hallway_pos - 1; pos >= destination; --pos) 
        {
          if (hallway[pos] != CellN::kEmpty) {
            path_clear = false;
            break;
          }
        }
      }

      if (!path_clear) 
        continue;

      const int hallway_path_length = std::abs(hallway_pos - destination);
      const std::optional<int> dest_room_position = FreeCellInDestinationRoom(source_cell);
      if (!dest_room_position.has_value()) 
        continue;

      StateN successor = *this;
      successor.hallway[hallway_pos] = CellN::kEmpty;
      successor.DestinationRoom(source_cell)[*dest_room_position] = source_cell;
      const int64_t cost = (hallway_path_length + 1 + *dest_room_position) * Energy(source_cell);
      successors.emplace_back(std::move(successor), cost);
    }

    // Moving from rooms -> hallway.
    for (const CellN room_type : {CellN::kA, CellN::kB, CellN::kC, CellN::kD})
    {
      const std::optional<int> initial_room_pos =
        FindMovableFromRoom(room_type);
      if (!initial_room_pos.has_value()) continue;

      const std::array<CellN, kRoomSize>& source_room =
        DestinationRoom(room_type);

      const int starting_room_position = RoomPosition(room_type);
      for (int final_hallway_pos = starting_room_position; final_hallway_pos >= 0; --final_hallway_pos) 
      {
        if (hallway[final_hallway_pos] != CellN::kEmpty) 
          break;

        if (final_hallway_pos == 2 || final_hallway_pos == 4 || final_hallway_pos == 6 || final_hallway_pos == 8)
          continue;

        StateN successor = *this;
        successor.DestinationRoom(room_type)[*initial_room_pos] = CellN::kEmpty;
        successor.hallway[final_hallway_pos] = source_room[*initial_room_pos];
        const int64_t cost = (*initial_room_pos + 1 + starting_room_position - final_hallway_pos) * Energy(source_room[*initial_room_pos]);
        successors.emplace_back(std::move(successor), cost);
      }

      for (int final_hallway_pos = starting_room_position; final_hallway_pos < 11; ++final_hallway_pos) 
      {
        if (hallway[final_hallway_pos] != CellN::kEmpty) 
          break;

        if (final_hallway_pos == 2 || final_hallway_pos == 4 || final_hallway_pos == 6 || final_hallway_pos == 8)
          continue;

        StateN successor = *this;
        successor.DestinationRoom(room_type)[*initial_room_pos] = CellN::kEmpty;
        successor.hallway[final_hallway_pos] = source_room[*initial_room_pos];
        const int64_t cost = (*initial_room_pos + 1 + final_hallway_pos - starting_room_position) * Energy(source_room[*initial_room_pos]);
        successors.emplace_back(std::move(successor), cost);
      }
    }

    return successors;
  }

  bool operator==(const StateN& other) const
  {
    return hallway == other.hallway && room_a == other.room_a &&
      room_b == other.room_b && room_c == other.room_c &&
      room_d == other.room_d;
  }

  template <typename H>
  friend H hashValue(H h, const StateN& state)
  {
    return H::combine(std::move(h), state.hallway, state.room_a, state.room_b,
      state.room_c, state.room_d);
  }

private:
  const std::array<CellN, kRoomSize>& DestinationRoom(const CellN cell) const 
  {
    switch (cell) 
    {
      case CellN::kEmpty:
        std::exit(1);
      case CellN::kA:
        return room_a;
      case CellN::kB:
        return room_b;
      case CellN::kC:
        return room_c;
      case CellN::kD:
        return room_d;
    }
  }

  std::array<CellN, kRoomSize>& DestinationRoom(const CellN cell) 
  {
    switch (cell) {
    case CellN::kEmpty:
      std::exit(1);
    case CellN::kA:
      return room_a;
    case CellN::kB:
      return room_b;
    case CellN::kC:
      return room_c;
    case CellN::kD:
      return room_d;
    }
  }

  std::optional<int> FreeCellInDestinationRoom(const CellN cell) const 
  {
    const std::array<CellN, kRoomSize>& room = DestinationRoom(cell);
    for (int pos = 0; pos < kRoomSize; ++pos) 
    {
      if (room[pos] == CellN::kEmpty) 
      {
        continue;
      }
      else if (pos == 0) 
      {
        return std::nullopt;
      }

      for (int bottom_pos = pos; bottom_pos < kRoomSize; ++bottom_pos) 
      {
        if (room[bottom_pos] != cell) 
          return std::nullopt;
      }
      return pos - 1;
    }
    return kRoomSize - 1;
  }

  std::optional<int> FindMovableFromRoom(const CellN cell) const 
  {
    const std::array<CellN, kRoomSize>& room = DestinationRoom(cell);
    for (int pos = 0; pos < kRoomSize; ++pos) 
    {
      if (room[pos] == CellN::kEmpty) 
        continue;

      if (room[pos] != cell) 
        return pos;

      for (int bottom_pos = pos + 1; bottom_pos < kRoomSize; ++bottom_pos) 
      {
        if (room[bottom_pos] != cell) 
          return pos;
      }
      return std::nullopt;
    }
    return std::nullopt;
  }
};

constexpr StateN kGoalStateN{ .hallway = {},
                              .room_a = {CellN::kA, CellN::kA, CellN::kA, CellN::kA},
                              .room_b = {CellN::kB, CellN::kB, CellN::kB, CellN::kB},
                              .room_c = {CellN::kC, CellN::kC, CellN::kC, CellN::kC},
                              .room_d = {CellN::kD, CellN::kD, CellN::kD, CellN::kD} };


struct stateNHash
{
  size_t operator()(const StateN& s) const
  {
    size_t result = 0;
    size_t aux = s.hallway.size();
    size_t aux2 = 2;

    for (auto& h : s.hallway)
      aux += (aux << 1) + static_cast<std::underlying_type_t<CellN>>(h) * 3;

    for (auto& room : { s.room_a, s.room_b,s.room_c, s.room_d })
      for (auto& h : room)
        aux2 += (aux2 << 1) + static_cast<std::underlying_type_t<CellN>>(h) * 5;

    result = std::hash<size_t>()((aux * 39) ^ aux2);

    return result;
  }
};

struct stateNPairHash
{
  std::size_t operator() (const std::pair<StateN, StateN>& pair) const
  {
    return (stateNHash()(pair.first) * 39) ^ stateNHash()(pair.second);
  }
};