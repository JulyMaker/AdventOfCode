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
#include <robin_hood.h>

struct food {
  std::vector<std::string> ingredients;
  std::vector<std::string> allergens;

  bool contains_ingredient(std::string const& ingredient) const
  {
    return std::binary_search(ingredients.begin(), ingredients.end(), ingredient);
  }

  bool contains_allergen(std::string const& allergen) const
  {
    return std::binary_search(allergens.begin(), allergens.end(), allergen);
  }

  void remove_ingredient(std::string const& ingredient)
  {
    ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), ingredient), ingredients.end());
  }

  void remove_allergen(std::string const& allergen)
  {
    allergens.erase(std::remove(allergens.begin(), allergens.end(), allergen), allergens.end());
  }
};

void process(std::vector<food>& recipes, robin_hood::unordered_set<std::string>& ingredients, robin_hood::unordered_set<std::string>& allergens, std::string& line)
{
  std::string aller;
  std::string ing;
  std::smatch sm;
  std::regex regExp("(.*) \\(contains (.*)\\)");

  if (regex_search(line, sm, regExp))
  {
    food foodd;

    std::stringstream s1(sm[1].str());
    while (getline(s1, ing, ' '))
    {
      if (ing[0] == ' ') ing.erase(ing.begin());
      foodd.ingredients.push_back(ing);   
      ingredients.insert(foodd.ingredients.back());
    }
    
    std::stringstream s2(sm[2].str());
    while (getline(s2, aller, ','))
    {
      if (aller[0] == ' ') aller.erase(aller.begin());
      foodd.allergens.push_back(aller);
      allergens.insert(foodd.allergens.back());
    }
    
    std::sort(foodd.ingredients.begin(), foodd.ingredients.end());
    std::sort(foodd.allergens.begin(), foodd.allergens.end());
    recipes.push_back(foodd);
  }
}

long long adventDay21problem1(std::vector<food>& recipes, robin_hood::unordered_set<std::string>& ingredients
  ,robin_hood::unordered_set<std::string>& allergens, std::vector<std::pair<std::string, std::string>>& list)
{
  int ingredientSize = ingredients.size();
  
  while (ingredients.size() != ingredientSize - allergens.size()) 
  {
    for (auto const& allergen : allergens) 
    {
      std::vector<std::string> v;

      for (auto const& recipe : recipes) 
      {
        if (!recipe.contains_allergen(allergen))       
          continue;
                   
        if (v.empty())  
          v = recipe.ingredients;         
        else    
          v.erase(std::remove_if(v.begin(), v.end(), [&](auto const& x) { return !recipe.contains_ingredient(x); }), v.end());         
      }

      if (v.size() == 1) 
      {
        auto const& ingredient = v.front();
        ingredients.erase(ingredient);

        list.push_back({ ingredient, allergen });

        for (auto& recipe : recipes) 
        {
          recipe.remove_ingredient(ingredient);
          recipe.remove_allergen(allergen);
        }
      }
    }
  }

  long long count = 0;
  for (auto const& ingredient : ingredients) 
  {
    count += std::count_if(recipes.begin(), recipes.end(), [&](auto const& recipe) { return recipe.contains_ingredient(ingredient); });
  }

  return count;
}

void adventDay21problem2(std::vector<std::pair<std::string, std::string>>& list)
{
  std::sort(list.begin(), list.end(), [](auto const& x, auto const& y) { return x.second < y.second; });
  bool first = false;
  for (auto& l : list) 
  {
    if (!first) { first = true;  std::cout << l.first; }
    std::cout << ","+l.first;
  } 

  std::cout << std::endl;
}


long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result=0;

  std::vector<food> recipes;
  robin_hood::unordered_set<std::string> ingredients;
  robin_hood::unordered_set<std::string> allergens;
  std::vector<std::pair<std::string, std::string>> list;

  while (!infile.eof())
  {
    std::getline(infile, line);
  
    if (line == "") continue;

    process(recipes, ingredients, allergens, line);
  }
  infile.close();

  result = adventDay21problem1(recipes, ingredients, allergens, list);
  if (problNumber == 2) adventDay21problem2(list);

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
   result = readFile(argv[1], 2);
   break;
 default:
   std::cout << "The number problem isn't right" << result << std::endl;
 }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}