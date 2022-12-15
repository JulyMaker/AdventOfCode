#include <utils.h>

using Point = std::pair<int64_t, int64_t>;
struct Sensor
{
  Point p;
  int64_t distance;
};


uint64_t adventDay15problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  int64_t Y = 2000000; // Problem 1 Value
  //Y = 10;    // Example value
  std::vector<Point> beacons;
  std::vector<Sensor> sensors;

  // Read input
  std::vector<std::string> in = parseInputReg(input, "Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)");
  for (int i=0; i < in.size()-4; i+=5)
  {
    Point beacon = {stoll(in[i + 3]), stoll(in[i + 4]) };
    beacons.push_back(beacon);

    Sensor sensor = Sensor();
    sensor.p = { stoll(in[i + 1]), stoll(in[i + 2]) };
    sensor.distance = std::abs(sensor.p.first - beacon.first) + std::abs(sensor.p.second - beacon.second);
    sensors.push_back(sensor);
  }
  
  // Fill grid
  int i = 0;
  std::vector<Point> outRange;
  for (auto& sensor : sensors)
  {
    int64_t delta = sensor.distance - std::abs(sensor.p.second - Y);
    if (delta >= 0)
    {
      int64_t left = sensor.p.first - delta;
      int64_t right = sensor.p.first + delta;
      if (beacons[i].second == Y)
      {
        if (left == beacons[i].first) left++;  
        else if (right == beacons[i].first) right--;
      }
      outRange.push_back({ left, right});
    }

    i++;
  }

  std::sort(outRange.begin(), outRange.end());

  // Solve
  std::vector<Point> solve;
  solve.push_back(outRange[0]);
  outRange.erase(outRange.begin());

  for(auto&[x, y] : outRange)
  {
    if (solve.back().second < x - 1)
      solve.push_back({ x, y });
    else if (solve.back().second < y)
      solve.back().second = y;
  }

  int64_t solv = 0;
  for (auto& s : solve) solv += std::abs(s.second - s.first + 1);
 
  std::cout << "Solucion:  " << solv << std::endl;
  return score;
}


uint64_t adventDay15problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  const int64_t XMAX = 4000000;
  std::vector<Point> beacons;
  std::vector<Sensor> sensors;

  // Read input
  std::vector<std::string> in = parseInputReg(input, "Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)");
  for (int i = 0; i < in.size() - 4; i += 5)
  {
    Point beacon = { stoll(in[i + 3]), stoll(in[i + 4]) };
    beacons.push_back(beacon);

    Sensor sensor = Sensor();
    sensor.p = { stoll(in[i + 1]), stoll(in[i + 2]) };
    sensor.distance = std::abs(sensor.p.first - beacon.first) + std::abs(sensor.p.second - beacon.second);
    sensors.push_back(sensor);
  }

  // Credits Topaz
  for (int64_t currY = 0; currY <= XMAX; currY++)
  {
    std::vector<Point> xIntervals;
    for (auto& sensor : sensors)
    {
      // for each sensor, get the range of x coordinates where there can't be a beacon
      // retrieve x offset range by deduction the y travel needed to reach the current y coordinate
      int64_t delta = sensor.distance - std::abs(sensor.p.second - currY);
      if (delta < 0) continue;

      // limit intervals to [0, 4000000]
      xIntervals.push_back({std::max(sensor.p.first - delta, (int64_t)0) , std::min(sensor.p.first + delta, XMAX)});
    }

    // sort the intervals so we can check them in order
    std::sort(xIntervals.begin(), xIntervals.end());

    Point currInterval = xIntervals[0];
    xIntervals.erase(xIntervals.begin());

    // after processing the intervals, all but 1 will end up with [0, 4000000]
    for (Point xInterval : xIntervals)
    {
      // if interval is completely inside the current interval, skip
      // eg. [20, 25] is completely inside [15, 30]
      if (currInterval.first <= xInterval.first && xInterval.second <= currInterval.second)
        continue;

      // if interval extends the current interval, extend current interval
      // eg. [20, 25] extends [15, 22] -> [15, 25]
      else if (currInterval.first <= xInterval.first && currInterval.second <= xInterval.second && xInterval.first <= currInterval.second)
        currInterval.second = xInterval.second;

      // if interval is out of bounds of the current interval, use the interval next
      // eg. [40, 50] is out of bounds of [52, 65]
      // this indicates that (51, currY) is the only possible coordinate
      else
      {
        int64_t distressX = currInterval.second + 1;
        std::cout << "Solucion:  " << distressX * XMAX + currY << std::endl;
        
        return score;
      }
    }
  }
   
  return score;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "15";

  std::string fileName = DAY_PATH(day);
  //fileName = DAY_EXAMPLE_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay15problem12022(inputFile); break;
    case 2: result = adventDay15problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}