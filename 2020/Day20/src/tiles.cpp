#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>

enum class EDGE{UP, DOWN, LEFT, RIGHT};

struct tile
{
  int id;

  bool upb; bool downb; bool leftb; bool rightb;

  int pairs;

  std::string up; std::string down;
  std::string left; std::string right;
};

struct tileEstructure
{
  int id;

  std::pair<int, bool> upb; std::pair<int, bool> downb; 
  std::pair<int, bool> leftb; std::pair<int, bool> rightb;

  int pairs;

  std::vector<std::string> ti;

  std::string up; std::string down;
  std::string left; std::string right;
};

template <class T>
void process(std::vector<T>& tiles, std::vector<std::string>& edges)
{
  T& t = tiles[tiles.size() - 1];

  std::string left;
  std::string right;
  for (auto& e : edges)
  {
    left += e[0];
    right+= e[e.size()-1];
  }

  t.up = edges[0];
  t.down = edges[edges.size() - 1];
  t.left = left;
  t.right = right;
}

void process(std::vector<tile>& tiles, std::string& line)
{
  //Tile 1217:
  std::smatch sm;
  std::regex regExp("Tile (\\d+):");

  if (regex_match(line, sm, regExp))
  {
    tile t;

    t.id = std::stoi(sm[1].str());
    t.upb = false; t.downb = false; t.leftb = false; t.rightb = false;
    t.pairs = 0;

    tiles.push_back(t);
  }
}

void processTile(std::vector<tileEstructure>& tiles, std::string& line)
{
  if (line == "") { process(tiles, tiles[tiles.size() - 1].ti); return; }

  std::smatch sm;
  std::regex regExp("Tile (\\d+):");

  if (regex_match(line, sm, regExp))
  {
    tileEstructure t;

    t.id = std::stoi(sm[1].str());
    t.upb.second = false; t.downb.second = false; t.leftb.second = false; t.rightb.second = false;
    t.pairs = 0;

    tiles.push_back(t);
  }
  else
  {
    tileEstructure& t = tiles[tiles.size() - 1];

    t.ti.push_back(line);
  }
}

bool check(std::string edge, tile& t2)
{
  std::string edgeR = edge;
  std::reverse(edgeR.begin(), edgeR.end());

  if (!t2.upb && (edge == t2.up || edgeR == t2.up)) { t2.pairs++; return t2.upb = true; }   
  if (!t2.downb && (edge == t2.down || edgeR == t2.down)) { t2.pairs++; return t2.downb = true; }
  if (!t2.leftb && (edge == t2.left || edgeR == t2.left)) { t2.pairs++; return t2.leftb = true; }
  if (!t2.rightb && (edge == t2.right || edgeR == t2.right)) { t2.pairs++; return t2.rightb = true; }
    
  return false;
}

void compare (tile& t1, tile& t2)
{
  if (!t1.upb)
    if (check(t1.up, t2)) { t1.upb = true; t1.pairs++; return; }
    
  if (!t1.downb)
    if (check(t1.down, t2)) { t1.downb = true; t1.pairs++; return; }
    
  if (!t1.leftb)
    if (check(t1.left, t2)) { t1.leftb = true; t1.pairs++; return; }
    
  if (!t1.rightb)
    if (check(t1.right, t2)) { t1.rightb = true; t1.pairs++; return; }  
}

long long adventDay20problem1(std::vector<tile>& tiles)
{
  for (int i = 0; i < tiles.size()-1; ++i)
    for (int j = i+1; j < tiles.size(); ++j)
      compare(tiles[i], tiles[j]);
       
  long long result = 1;
  for (auto& t : tiles)
  {
    if (t.pairs == 2)
      result *= t.id;
  }
    
  return result;
}

bool check(std::string edge, tileEstructure& t2, int index1)
{
  std::string edgeR = edge;
  std::reverse(edgeR.begin(), edgeR.end());

  if (!t2.upb.second && (edge == t2.up || edgeR == t2.up)) { t2.pairs++; t2.upb.first = index1; return t2.upb.second = true; }
  if (!t2.downb.second && (edge == t2.down || edgeR == t2.down)) { t2.pairs++; t2.downb.first = index1; return t2.downb.second = true; }
  if (!t2.leftb.second && (edge == t2.left || edgeR == t2.left)) { t2.pairs++; t2.leftb.first = index1; return t2.leftb.second = true; }
  if (!t2.rightb.second && (edge == t2.right || edgeR == t2.right)) { t2.pairs++; t2.rightb.first = index1; return t2.rightb.second = true; }

  return false;
}

void compare(tileEstructure& t1, tileEstructure& t2, int index1, int index2)
{
  if (!t1.upb.second)
    if (check(t1.up, t2, index1)) { t1.upb.second = true; t1.upb.first = index2; t1.pairs++; return; }

  if (!t1.downb.second)
    if (check(t1.down, t2, index1)) { t1.downb.second = true; t1.downb.first = index2; t1.pairs++; return; }

  if (!t1.leftb.second)
    if (check(t1.left, t2, index1)) { t1.leftb.second = true; t1.leftb.first = index2; t1.pairs++; return; }

  if (!t1.rightb.second)
    if (check(t1.right, t2, index1)) { t1.rightb.second = true; t1.rightb.first = index2; t1.pairs++; return; }
}

void flip(tileEstructure& ctile, bool vertical)
{
  std::string aux;
  std::vector<std::string> auxv;
  std::pair<int, bool> auxp;
  if (vertical)
  {
    for (int i=ctile.ti.size()-1; i>=0; --i)
      auxv.push_back(ctile.ti[i]);

    ctile.ti = auxv;

    aux = ctile.up;
    ctile.up = ctile.down;
    ctile.down = aux;

    std::reverse(ctile.right.begin(), ctile.right.end());
    std::reverse(ctile.left.begin(), ctile.left.end());

    auxp = ctile.upb;
    ctile.upb = ctile.downb;
    ctile.downb = auxp;
  }
  else // horizontal
  {
    for (int i = 0; i < ctile.ti.size(); ++i)
    {
      aux = ctile.ti[i];
      std::reverse(aux.begin(), aux.end());
      auxv.push_back(aux);
    }
      
    ctile.ti = auxv;

    aux = ctile.left;
    ctile.left = ctile.right;
    ctile.right = aux;

    std::reverse(ctile.up.begin(), ctile.up.end());
    std::reverse(ctile.down.begin(), ctile.down.end());

    auxp = ctile.leftb;
    ctile.leftb = ctile.rightb;
    ctile.rightb = auxp;
  }
}

void turn(tileEstructure& ctile, bool right)
{
  std::string aux;
  std::vector<std::string> auxv;
  std::pair<int, bool> auxp;
  if (right)
  {
    for(int row=0; row< ctile.ti[0].size(); ++row)
    {
      for (int i = ctile.ti.size() - 1; i >= 0; --i)
      {
        aux += ctile.ti[i][row];
      }
      auxv.push_back(aux);
      aux.clear();
    }
    
    ctile.ti = auxv;

    aux = ctile.up;
    ctile.up = ctile.left;
    std::reverse(ctile.up.begin(), ctile.up.end());
    ctile.left = ctile.down;
    ctile.down = ctile.right;
    std::reverse(ctile.down.begin(), ctile.down.end());
    ctile.right = aux;

    auxp = ctile.upb;
    ctile.upb = ctile.leftb;
    ctile.leftb = ctile.downb;
    ctile.downb = ctile.rightb;
    ctile.rightb = auxp;
  }
  else
  {
    for (int row = ctile.ti[0].size()-1; row >= 0 ; --row)
    {
      for (int i =0; i< ctile.ti.size(); ++i)
      {
        aux += ctile.ti[i][row];
      }
      auxv.push_back(aux);
      aux.clear();
    }

    ctile.ti = auxv;

    aux = ctile.up;
    ctile.up = ctile.right;
    ctile.right = ctile.down;
    std::reverse(ctile.right.begin(), ctile.right.end());
    ctile.down = ctile.left;
    ctile.left = aux;
    std::reverse(ctile.left.begin(), ctile.left.end());

    auxp = ctile.upb;
    ctile.upb = ctile.rightb;
    ctile.rightb = ctile.downb;
    ctile.downb = ctile.leftb;
    ctile.leftb = auxp;
  }
}

void placement(tileEstructure* currentTile, tileEstructure& tilesPos, int pos1, bool col)
{
  EDGE edge = EDGE::UP;
  if (tilesPos.upb.first == pos1 && tilesPos.upb.second) edge = EDGE::UP;
  else if (tilesPos.downb.first == pos1 && tilesPos.downb.second) edge = EDGE::DOWN;
  else if (tilesPos.leftb.first == pos1 && tilesPos.leftb.second) edge = EDGE::LEFT;
  else if (tilesPos.rightb.first == pos1 && tilesPos.rightb.second) edge = EDGE::RIGHT;

  if (col)
  {
    if (currentTile->right == tilesPos.left) return;
    
    switch (edge)
    {
    case EDGE::UP:
    {
      if (currentTile->right == tilesPos.up)
      {
        flip(tilesPos, true); turn(tilesPos, true);
      }
      else
      {
        turn(tilesPos, false);
      }
    }
        break;
    case EDGE::DOWN:
      if (currentTile->right == tilesPos.down)
      {
        turn(tilesPos, true);
      }
      else
      {
        flip(tilesPos, true); turn(tilesPos, false);
      }
      break;
    case EDGE::LEFT:
      flip(tilesPos, true);
      break;
    case EDGE::RIGHT:
      if (currentTile->right == tilesPos.right)
      {
        flip(tilesPos, false);
      }
      else
      {
        flip(tilesPos, false);
        flip(tilesPos, true);
      }
      break;
    }
  }
  else
  {
    if (currentTile->down == tilesPos.up) return;

    switch (edge)
    {
    case EDGE::UP:
    {
      flip(tilesPos, false);
    }
    break;
    case EDGE::DOWN:
      if (currentTile->down == tilesPos.down)
      {
        flip(tilesPos, true);
      }
      else
      {
        flip(tilesPos, false); flip(tilesPos, true);
      }
      break;
    case EDGE::LEFT:
      if (currentTile->down == tilesPos.left)
      {
        flip(tilesPos, true); turn(tilesPos, true);
      }
      else
      {
        turn(tilesPos, true);    
      }
      break;
    case EDGE::RIGHT:
      if (currentTile->down == tilesPos.right)
      {
        turn(tilesPos, false);
      }
      else
      {
        flip(tilesPos, true); turn(tilesPos, false);
      }
      break;
    }
  }
}

void turnSquare(tileEstructure& tile)
{
  if (tile.upb.second && tile.rightb.second)
  {
    turn(tile, true);
  }
  else if(tile.leftb.second && tile.downb.second)
  {
    turn(tile, false);
  }
  else if(tile.upb.second && tile.leftb.second)
  {
    turn(tile, true);
    turn(tile, true);
  }
}

void removeBorders(std::vector<std::vector<tileEstructure*>>& collageArr)
{
  std::vector<std::string> tiAux;

  for (auto& tA : collageArr)
  {
    for(auto& t: tA)
    {
      for (int i = 0; i < t->ti.size(); ++i)
      {
        if (i == 0 || i == t->ti.size() - 1) continue;
        int end = t->ti[i].size() - 2;
        tiAux.push_back(t->ti[i].substr(1,end));
      }

      t->ti = tiAux;
      tiAux.clear();
    }
  }
}

void finalCollage(std::vector<std::vector<tileEstructure*>>& collageArr, std::vector<std::string>& collage)
{
  for (auto& tA : collageArr)
  {
    for (int i = 0; i < tA[0]->ti.size(); ++i)
    {
      collage.push_back(tA[0]->ti[i]);
      for (int j=1; j< tA.size(); ++j)
      {
        collage[collage.size() - 1] = collage[collage.size() - 1] + tA[j]->ti[i];
      }
    }
  }
}

void printCollage(std::vector<std::string>& collage)
{
  for(auto& c : collage)
  {
    std::cout << c << std::endl;
  }
}

std::vector<std::string> imageCollage(std::vector<tileEstructure> tiles, int vertex)
{
  std::vector<std::string> collage;
  std::vector<std::vector<tileEstructure*>> collageArr;
  std::vector<tileEstructure*> arrAux;

  tileEstructure* firstTile;
  tileEstructure* firstTileRow;
  int cPos = 0, firstcPos=0;

  int squareVertex = 0;
  for(int tilePos=0; tilePos< tiles.size(); ++tilePos)
  {
    if (tiles[tilePos].pairs == 2)
    {
      if (squareVertex == vertex)
      {
        if (!tiles[tilePos].downb.second || !tiles[tilePos].rightb.second)
        {
          turnSquare(tiles[tilePos]);
        }
        // Begin 0 0 pos
        firstTileRow = &tiles[tilePos];
        firstTile = firstTileRow;
        cPos = tilePos;
        arrAux.push_back(firstTile);
        break;
      }
      else
      {
        squareVertex++;
      }
    }   
  }

  tileEstructure* currentTile = firstTileRow;
  firstcPos = cPos;
  //for(int i=0; i < sqrt; ++i)
  while(currentTile->rightb.second)
  {
    //for (int j = 1; j < sqrt; ++j)
    while(currentTile->rightb.second)
    {
      int pos = currentTile->rightb.first;    

      placement(currentTile, tiles[pos], cPos, true);
      currentTile = &tiles[pos];
      cPos = pos;
      arrAux.push_back(currentTile);
    }

    collageArr.push_back(arrAux);
    arrAux.clear();

    if (!firstTileRow->downb.second) break;
    int posY = firstTileRow->downb.first;

    placement(firstTileRow, tiles[posY], firstcPos, false);
    currentTile = &tiles[posY];
    firstTileRow = currentTile;
    cPos = posY;
    firstcPos = posY;
    arrAux.push_back(currentTile);
  }

  removeBorders(collageArr);
  finalCollage(collageArr, collage);

  //printCollage(collage);
  return collage;
}

std::vector<int> foundBody(std::string s1, std::string s2)
{
  int pos = 0;
  int current = 0;
  std::vector<int> posi;

  while(s2.size()+pos <= s1.size())
  {
    if (s2[current] == '#' && s1[pos+current] == '#')
    {
      current++;
    }
    else if(s2[current]==' ')
    {
      current++;
    }
    else
    {
      pos++;
      current = 0;
    }

    if (current == s2.size())
    {
      posi.push_back(pos);
      pos++;
      current = 0;
    }
  }

  return posi;
}

long long monsterPattern(std::vector<std::string>& image)
{
  std::string s0 = "                  # ";
  std::string s1 = "#    ##    ##    ###";
  std::string s2 = " #  #  #  #  #  #   ";

  std::vector<std::string> monster{s0, s1, s2};
  auto mons_num = std::count(monster[0].begin(), monster[0].end(), '#')+
                  std::count(monster[1].begin(), monster[1].end(), '#')+ 
                  std::count(monster[2].begin(), monster[2].end(), '#');

  bool printMonster = false;
  int repeat = 0;
  for(int i=1; i<image.size()-1; ++i)
  {
    std::vector<int> posi = foundBody(image[i], s1);
    for (int j = 0; j < posi.size(); ++j)//if (pos != -1)
    {
      int pos = posi[j];

      bool foundHead = image[i - 1][pos + 18] == '#';
      if (foundHead)
      {
        bool foundFoot = image[i + 1][pos + 1]  == '#' &&
                         image[i + 1][pos + 4]  == '#' &&
                         image[i + 1][pos + 7]  == '#' &&
                         image[i + 1][pos + 10] == '#' &&
                         image[i + 1][pos + 13] == '#' &&
                         image[i + 1][pos + 16] == '#';

        if (foundFoot) 
        {
          repeat++;
          
          printMonster = true;
          if (printMonster)
          {
            image[i - 1][pos + 18] = '0';
            image[i + 1][pos + 1]  = '0';
            image[i + 1][pos + 4]  = '0';
            image[i + 1][pos + 7]  = '0';
            image[i + 1][pos + 10] = '0';
            image[i + 1][pos + 13] = '0';
            image[i + 1][pos + 16] = '0';
            image[i][pos]          = '0';
            image[i][pos + 5]      = '0';
            image[i][pos + 6]      = '0';
            image[i][pos + 11]     = '0';
            image[i][pos + 12]     = '0';
            image[i][pos + 17]     = '0';
            image[i][pos + 18]     = '0';
            image[i][pos + 19]     = '0';
          }
          
        } 
      }   
    }
  }
  
  if(printMonster) printCollage(image);
  long long countPad = 0;
  
  if (repeat > 0)
  {
    for (auto& line : image)
    {
      countPad += std::count(line.begin(), line.end(), '#');
    }
    //countPad -= repeat * mons_num; //If not change X to 0
  }
  
  return countPad;
}

void turnImage(std::vector<std::string>& image)
{
  std::string aux;
  std::vector<std::string> auxv;
  for (int row = 0; row < image.size(); ++row)
  {
    for (int i = image.size() - 1; i >= 0; --i)
    {
      aux += image[i][row];
    }
    auxv.push_back(aux);
    aux.clear();
  }

  image = auxv;
}

void flipImage(std::vector<std::string>& image)
{
  std::vector<std::string> auxv;
  for (int i = image.size() - 1; i >= 0; --i)
    auxv.push_back(image[i]);

  image = auxv;
}

long long adventDay20problem2(std::vector<tileEstructure>& tiles)
{
  long long result = 0;

  for (int i = 0; i < tiles.size() - 1; ++i)
    for (int j = i + 1; j < tiles.size(); ++j)
      compare(tiles[i], tiles[j], i, j);

  int vertex = 0;
  std::vector<std::string> image = imageCollage(tiles, vertex);
  
  int loop = 0;
  while (result == 0)
  {
    result = monsterPattern(image);
    if (loop == 3 && result==0)
      flipImage(image);
    else if (result == 0)
      turnImage(image);

    loop++;
  }
  
  return result;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result=0;
  std::vector<tile> tiles;
  std::vector<std::string> edges;

  while (!infile.eof())
  {
    std::getline(infile, line); //id
    if (line == "") continue;
    process(tiles, line);

    for (int i = 0; i < 10; ++i)
    {
      std::getline(infile, line);
      edges.push_back(line);
    }
    process(tiles, edges);
    edges.clear();

    std::getline(infile, line);
    
  }
  infile.close();

  result = adventDay20problem1(tiles);

  return result;
}

long long int readFile2(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result = 0;
  std::vector<tileEstructure> tiles;

  while (!infile.eof())
  {
    std::getline(infile, line);
    processTile(tiles, line);
  }
  infile.close();

  result = adventDay20problem2(tiles);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 3)
 {
   std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[2]))
 {
 case 1:
   result = readFile(argv[1], 1);
   break;
 case 2:
   result = readFile2(argv[1], 2);
   break;
 default:
   std::cout << "The number problem isn't right" << result << std::endl;
 }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}