#include <algorithm>
#include <array>
#include <vector>


enum class Cell : char { kEmpty = 0, kA, kB, kC, kD };

Cell parseCell(const char c) 
{
  switch (c) 
  {
    case '.':
      return Cell::kEmpty;
    case 'A':
      return Cell::kA;
    case 'B':
      return Cell::kB;
    case 'C':
      return Cell::kC;
    case 'D':
      return Cell::kD;
  }
}

int roomPosition(const Cell cell) 
{
  switch (cell) 
  {
    case Cell::kEmpty:
      std::exit(1);
    case Cell::kA:
      return 2;
    case Cell::kB:
      return 4;
    case Cell::kC:
      return 6;
    case Cell::kD:
      return 8;
  }
}

int64_t energy(const Cell cell) 
{
  switch (cell) 
  {
    case Cell::kEmpty:
      std::exit(1);
    case Cell::kA:
      return 1;
    case Cell::kB:
      return 10;
    case Cell::kC:
      return 100;
    case Cell::kD:
      return 1000;
  }
}

struct State 
{
  std::array<Cell, 11> hallWay;
  std::array<Cell, 2> roomA;
  std::array<Cell, 2> roomB;
  std::array<Cell, 2> roomC;
  std::array<Cell, 2> roomD;

  std::vector<std::pair<State, int64_t>> successorStates() const 
  {
    std::vector<std::pair<State, int64_t>> successors;

    // Moving Amphipods -> Final Rooms.
    for (int hallwayPos = 0; hallwayPos < 11; ++hallwayPos)
    {
      const Cell sourceCell = hallWay[hallwayPos];
      if (sourceCell == Cell::kEmpty)
        continue;

      int destination = roomPosition(sourceCell);
      bool pathClear = true;
      if (hallwayPos < destination) 
      {
        for (int pos = hallwayPos + 1; pos <= destination; ++pos)
        {
          if (hallWay[pos] != Cell::kEmpty) 
          {
            pathClear = false;
            break;
          }
        }
      }
      else 
      {
        for (int pos = hallwayPos - 1; pos >= destination; --pos)
        {
          if (hallWay[pos] != Cell::kEmpty) 
          {
            pathClear = false;
            break;
          }
        }
      }

      if (!pathClear) 
        continue;

      const int hallway_path_length = std::abs(hallwayPos - destination);
      const std::array<Cell, 2>& dest = destinationRoom(sourceCell);
      if (dest[0] != Cell::kEmpty) 
        continue;

      if (dest[1] == Cell::kEmpty) 
      {
        State successor = *this;
        successor.hallWay[hallwayPos] = Cell::kEmpty;
        successor.destinationRoom(sourceCell)[1] = sourceCell;

        const int64_t cost = (hallway_path_length + 2) * energy(sourceCell);
        successors.emplace_back(std::move(successor), cost);
      }
      else if (dest[1] == sourceCell) 
      {
        State successor = *this;
        successor.hallWay[hallwayPos] = Cell::kEmpty;
        successor.destinationRoom(sourceCell)[0] = sourceCell;

        const int64_t cost = (hallway_path_length + 1) * energy(sourceCell);
        successors.emplace_back(std::move(successor), cost);
      }
    }

    // Moving from rooms -> hallway.
    for (const Cell room_type : {Cell::kA, Cell::kB, Cell::kC, Cell::kD}) 
    {
      const std::array<Cell, 2>& sourceRoom = destinationRoom(room_type);
      
      if (sourceRoom[0] == room_type && sourceRoom[1] == room_type) continue;

      int initialRoomPos = 0;
      if (sourceRoom[0] != Cell::kEmpty)
      {
        initialRoomPos = 0;
      }
      else 
      {
        if (sourceRoom[1] == Cell::kEmpty || sourceRoom[1] == room_type)
          continue;
        initialRoomPos = 1;
      }

      const int starting_room_position = roomPosition(room_type);
      for (int final_hallway_pos = starting_room_position; final_hallway_pos >= 0; --final_hallway_pos)
      {
        if (hallWay[final_hallway_pos] != Cell::kEmpty) 
          break;

        if (final_hallway_pos == 2 || final_hallway_pos == 4 || final_hallway_pos == 6 || final_hallway_pos == 8) 
          continue;

        State successor = *this;
        successor.destinationRoom(room_type)[initialRoomPos] = Cell::kEmpty;
        successor.hallWay[final_hallway_pos] = sourceRoom[initialRoomPos];
        const int64_t cost = (initialRoomPos + 1 + starting_room_position - final_hallway_pos) * energy(sourceRoom[initialRoomPos]);

        successors.emplace_back(std::move(successor), cost);
      }

      for (int final_hallway_pos = starting_room_position; final_hallway_pos < 11; ++final_hallway_pos) 
      {
        if (hallWay[final_hallway_pos] != Cell::kEmpty) 
          break;

        if (final_hallway_pos == 2 || final_hallway_pos == 4 || final_hallway_pos == 6 || final_hallway_pos == 8) 
          continue;

        State successor = *this;
        successor.destinationRoom(room_type)[initialRoomPos] = Cell::kEmpty;
        successor.hallWay[final_hallway_pos] = sourceRoom[initialRoomPos];
        const int64_t cost = (initialRoomPos + 1 + final_hallway_pos - starting_room_position) * energy(sourceRoom[initialRoomPos]);

        successors.emplace_back(std::move(successor), cost);
      }
    }

    return successors;
  }

  bool operator==(const State& other) const 
  {
    return hallWay == other.hallWay && roomA == other.roomA && roomB == other.roomB && 
                      roomC == other.roomC && roomD == other.roomD;
  }

  bool operator!=(const State& other) const
  {
    return hallWay != other.hallWay || roomA != other.roomA || roomB != other.roomB ||
      roomC != other.roomC || roomD != other.roomD;
  }

  template <typename H>
  friend H hashValue(H h, const State& state) 
  {
    return H::combine(std::move(h), state.hallway, state.room_a, state.room_b, state.room_c, state.room_d);
  }

private:
  const std::array<Cell, 2>& destinationRoom(const Cell cell) const 
  {
    switch (cell) 
    {
      case Cell::kEmpty:
        std::exit(1);
      case Cell::kA:
        return roomA;
      case Cell::kB:
        return roomB;
      case Cell::kC:
        return roomC;
      case Cell::kD:
        return roomD;
    }
  }

  std::array<Cell, 2>& destinationRoom(const Cell cell) 
  {
    switch (cell) 
    {
      case Cell::kEmpty:
        std::exit(1);
      case Cell::kA:
        return roomA;
      case Cell::kB:
        return roomB;
      case Cell::kC:
        return roomC;
      case Cell::kD:
        return roomD;
    }
  }
};

constexpr State kGoalState{ .hallWay = {},.roomA = {Cell::kA, Cell::kA}, .roomB = {Cell::kB, Cell::kB},
                            .roomC = {Cell::kC, Cell::kC},.roomD = {Cell::kD, Cell::kD} };

struct stateHash
{
  size_t operator()(const State& s) const
  {
    size_t result = 0;
    size_t aux = s.hallWay.size();
    size_t aux2 = 2;
    
    for (auto& h : s.hallWay)
      aux += (aux << 1) + static_cast<std::underlying_type_t<Cell>>(h) * 3;
    
    for (auto& room : { s.roomA, s.roomB,s.roomC, s.roomD })
      for (auto& h : room)
        aux2 += (aux2 << 1) + static_cast<std::underlying_type_t<Cell>>(h) * 5;
    
    result = std::hash<size_t>()((aux * 39) ^ aux2);

    return result;
  }
};

struct statePairHash
{
  std::size_t operator() (const std::pair<State, State>& pair) const
  {
    return (stateHash()(pair.first)*39) ^ stateHash()(pair.second);
  }
};