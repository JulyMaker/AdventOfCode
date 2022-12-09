#include <utils.h>

uint64_t adventDay08problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::vector<std::vector<int>> grid = parseInputGrid(input);
  
  score = (grid.size() * 2) + (grid[0].size() * 2) - 4; // edges

  for(int i=1; i < grid.size() - 1; i++)
    for (int j = 1; j < grid[0].size() - 1; j++)
    {   
      int up    = j;
      int down  = j;
      int right = i;
      int left  = i;

      bool isVisible = false;
      bool outOfGrid = false;

      do
      {
        if (up    != -1) up--;
        if (down  != -1) down++;
        if (right != -1) right++;
        if (left  != -1) left--;

        if ((up    != -1) && grid[i][up]    >= grid[i][j]) up    = -1; //up
        if ((down  != -1) && grid[i][down]  >= grid[i][j]) down  = -1; //down
        if ((right != -1) && grid[right][j] >= grid[i][j]) right = -1; //right
        if ((left  != -1) && grid[left][j]  >= grid[i][j]) left  = -1; //left

        isVisible = (up == 0) || (left == 0) || (down == grid.size() - 1) || (right == grid[0].size() - 1);
        outOfGrid = (up == -1) && (left == -1) && (down == -1) && (right == -1);

      } while (!outOfGrid && !isVisible);

      if (isVisible) score++;
    }

  return score;
}

uint64_t adventDay08problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  std::vector<std::vector<int>> grid = parseInputGrid(input);
  for (int i = 1; i < grid.size() - 1; i++)
    for (int j = 1; j < grid[0].size() - 1; j++)
    {
      int up = j;
      int down = j;
      int right = i;
      int left = i;

      int treeScore[4] = {0,0,0,0}; // up, down, rigth, left
      bool outOfGrid = false;

      do
      {
        if (up    != -1) up--;
        if (down  != -1) down++;
        if (right != -1) right++;
        if (left  != -1) left--;

        if (down  > grid.size() - 1)    down  = -1;
        if (right > grid[0].size() - 1) right = -1;

        if (up != -1) treeScore[0]++;
        if ((up != -1) && grid[i][up] >= grid[i][j]) up = -1; //up

        if (down != -1) treeScore[1]++;
        if ((down  != -1) && grid[i][down]  >= grid[i][j]) down  = -1; //down

        if (right != -1) treeScore[2]++;
        if ((right != -1) && grid[right][j] >= grid[i][j]) right = -1; //right 

        if (left != -1) treeScore[3]++;
        if ((left  != -1) && grid[left][j]  >= grid[i][j]) left  = -1; //left
 
        outOfGrid = (up == -1) && (left == -1) && (down == -1) && (right == -1);

      } while (!outOfGrid);

      uint64_t treeSc = treeScore[0] * treeScore[1] * treeScore[2] * treeScore[3];
      score = std::max(score, treeSc);
    }

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "08";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay08problem12022(inputFile); break;
    case 2: result = adventDay08problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}