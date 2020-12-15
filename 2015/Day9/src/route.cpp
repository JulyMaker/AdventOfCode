#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>

struct Edge {
  std::string origen;     //Vértice origen
  std::string destino;    //Vértice destino
  int peso;               //Peso entre el vértice origen y destino
  Edge() {}
  //Comparador por peso, me servira al momento de ordenar lo realizara en orden ascendente
  //Cambiar signo a > para obtener el arbol de expansion maxima
  bool operator<(const Edge &e) const {
    return peso < e.peso;
  }
};

//Método para encontrar la raiz del vértice actual X
std::string Find(std::string x, std::set<std::string>& cities, std::vector<std::string>& padre)
{
  int pos = std::distance(cities.begin(), cities.find(x));
  return (x == padre[pos]) ? x : padre[pos] = Find(padre[pos], cities, padre);
}

//Método que me determina si 2 vértices estan o no en la misma componente conexa
bool sameComponent(std::string x, std::string y, std::set<std::string>& cities, std::vector<std::string>& padre) 
{
  if (Find(x, cities, padre) == Find(y, cities, padre)) return true;
  return false;
}

//Método para unir 2 componentes conexas
void union2(std::string x, std::string y, std::set<std::string>& cities, std::vector<std::string>& padre)
{
  int pos = std::distance(cities.begin(), cities.find(Find(x, cities, padre)));
  padre[pos] = Find(y, cities, padre);
}

void process(std::vector<Edge>& routes, std::set<std::string>& cities, std::string& line)
{
  //Faerun to Tristram = 65
  std::smatch sm;
  std::regex regExp("(\\w+) to (\\w+) = (\\d+)");

  if (regex_search(line, sm, regExp))
  {
    Edge edge;
    edge.origen = sm[1].str();
    edge.destino = sm[2].str();
    edge.peso = std::stoi(sm[3].str());

    cities.insert(edge.origen);
    cities.insert(edge.destino);

    routes.push_back(edge);
  }
}

int kruskal(std::vector<Edge>& routes, std::set<std::string>& cities)
{
  std::vector<Edge> mst;
  std::vector<std::string> padre;

  std::string origen, destino;
  int total = 0;          //Peso total del MST
  int numAristas = 0;     //Numero de Aristas del MST

  //Inicializamos cada componente
  for (std::set<std::string>::iterator it = cities.begin(); it != cities.end(); ++it)
  {
    padre.push_back(*it);
  }
    
  //Ordenamos las aristas por su comparador
  std::sort(routes.begin(), routes.end());

  for (int i = 0; i < routes.size(); ++i)  //Recorremos las aristas ya ordenadas por peso
  {     
    origen = routes[i].origen;    //Vértice origen de la arista actual
    destino = routes[i].destino;  //Vértice destino de la arista actual

    //Verificamos si estan o no en la misma componente conexa
    if (!sameComponent(origen, destino, cities, padre)) //Evito ciclos
    {  
      total += routes[i].peso;                   //Incremento el peso total del MST
      mst.push_back(routes[i]);                  //Agrego al MST la arista actual
      union2(origen, destino, cities, padre);    //Union de ambas componentes en una sola
    }
  }

    //Si el MST encontrado no posee todos los vértices mostramos mensaje de error
    //Para saber si contiene o no todos los vértices basta con que el numero
    //de aristas sea igual al numero de vertices - 1
  if (padre.size() - 1 != mst.size()) {
    std::cout << "No existe MST valido para el grafo ingresado, el grafo debe ser conexo." << std::endl;
    return 0;
  }
  std::cout << "-----El MST encontrado contiene las siguientes aristas-----" << std::endl;
  for (int i = 0; i < mst.size(); ++i)
    printf("( %s , %s ) : %d\n", mst[i].origen.c_str(), mst[i].destino.c_str(), mst[i].peso); //( vertice u , vertice v ) : peso


  return total;
}

int get_id(const std::string & city)
{
  static int shist = 0;
  static std::unordered_map <std::string, int> lookup;
  auto && loc = lookup.find(city);
  if (loc != std::end(lookup))
    return loc->second;
  return (lookup[city] = 1 << shist++);
}

int adventDay9problem12015(std::vector<Edge>& routes)
{ 
  std::set <int> cities;
  std::unordered_map <int, int> distances;
  for (auto && edge : routes) {
    int h1{ get_id(edge.origen) }, h2{ get_id(edge.destino )};
    cities.insert(h1), cities.insert(h2), distances[h1 | h2] = edge.peso;
  }

  std::vector <int> order{ cities.cbegin(), cities.cend() };

  int distance = std::numeric_limits <int>::max();
  do {
    int current = 0;

    for (auto && c = order.cbegin() + 1; c != order.cend(); ++c)
      current += distances[*c | *(c - 1)];

    distance = std::min(distance, current);
  } while (std::next_permutation(order.begin(), order.end()));

  return distance;
}

int adventDay9problem22015(std::vector<Edge>& routes)
{
  std::set <int> cities;
  std::unordered_map <int, int> distances;
  for (auto && edge : routes) {
    int h1{ get_id(edge.origen) }, h2{ get_id(edge.destino) };
    cities.insert(h1), cities.insert(h2), distances[h1 | h2] = edge.peso;
  }

  std::vector <int> order{ cities.cbegin(), cities.cend() };

  int distance = 0;
  do {
    int current = 0;

    for (auto && c = order.cbegin() + 1; c != order.cend(); ++c)
      current += distances[*c | *(c - 1)];

    distance = std::max(distance, current);
  } while (std::next_permutation(order.begin(), order.end()));

  return distance;
}

unsigned short readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<Edge> routes;
  std::set<std::string> cities;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;

    if (line == "") continue;
    process(routes, cities, line);
    
  }
  infile.close();

  return (problNumber == 1) ? adventDay9problem12015(routes)
                            : adventDay9problem22015(routes);

}

unsigned short main(int argc, char *argv[])
{
  // argv contain txt path
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

  int result = 0;
  switch (std::stoi(argv[2]))
  {
  case 1:
    result = readFile(argv[1], 1);
    break;
  case 2:
    result = readFile(argv[1], 2);
    break;
  default:
    std::cout << "The problem number isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}