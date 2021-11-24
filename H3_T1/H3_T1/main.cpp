#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <limits>

// Функция для вывода дерева путей на экран в том виде,
// в котором сказано в задании
void printTree(std::vector<std::list<int>>& pathsTree, int startV, int indent = 0);

//Класс Графа
class Graph
{
public:

	//Конструкторы
	Graph() = default;
	Graph(int size) { data_.resize(size); }
	~Graph() = default;

	//Функция добавления ребра между вершинами
	void addEdge(int numSrc, int numDest, float weight)
	{
		data_[numSrc].push_back(std::make_pair<>(numDest, weight));
	}

	//Алгоритм Беллмана-Форда для вершины с номером startV
	std::unique_ptr<std::vector<float>> BellmanFordShortestPaths(int startV)
	{
    //Преобразуем граф в массив рёбер для возможности просмотра всех рёбер за 0(E)
		struct Edge
		{
			int u, v;
			float w;
		};
		std::list<Edge> edges;
		
		for (int i = 0; i < data_.size(); ++i)
		{
			for (auto& j : data_[i])
			{
				edges.push_back(Edge{ i, j.first, j.second });
			}
		}
		//Бесконечность для типа float (любое float < INF)
		constexpr float inf = std::numeric_limits<float>::infinity();

		bool existNegativeCycle = false;
		std::vector<float> d(data_.size(), inf);
		d[startV] = 0.0f;

		std::vector<int> cameFrom(data_.size(), -1);

		//Цикл по всем ребрам
		for (int i = 0; i < data_.size(); ++i)
		{
			bool isChanges = false;
			for (auto&e : edges)
			{
				//Если до вершины есть хоть какой-то путь, то можно релаксировать ребро
				if (d[e.u] != inf && d[e.u] + e.w < d[e.v])
				{
					isChanges = true;

					//update
					d[e.v] = d[e.u] + e.w;
					if (i == data_.size() - 1) existNegativeCycle = true;

					cameFrom[e.v] = e.u;
				}
			}

			//Если массив d не изменился - выходим из цикла
			if (!isChanges)
			{
				break;
			}
		}

		if (existNegativeCycle)
		{
			std::cout << "A negative-weight cycle is reachable from the source vertex";
			return nullptr;
		}

		//Выводим длины путей на экран
		std::cout << "The weight of a shortest path from vertex " << startV << " to vertex\n";
		std::for_each(d.begin(), d.end(), [](auto& x)
			{
				static int index = 0;
				std::cout << index << "  is  " << x << '\n';

				++index;
			});

		//Заполняем дерево путей
		std::vector<std::list<int>> pathsTree(data_.size());

		for (int i = 0; i < cameFrom.size(); ++i)
		{
			if (cameFrom[i] != -1) pathsTree[cameFrom[i]].push_back(i);
		}

		//Выводим дерево путей на экран
		std::cout << "\nA shortest paths tree:\n";
		printTree(pathsTree, startV);
		
		return std::make_unique<std::vector<float>>(d);
	}
	
private:

	std::vector<std::list<std::pair<int, float>>> data_;
};

//Функция для считывания вершины и записи её в граф g
void readVertex(Graph& g);

int main()
{
	//Считываем размер, вершины и стартовую точку
	int size;
	std::cin >> size;

	Graph g(size);

	for (int i = 0; i < size; ++i)
	{
		readVertex(g);
	}

	int startV;
	std::cin >> startV;

	std::unique_ptr<std::vector<float>> shortestPaths;
	std::cout << '\n';
	shortestPaths = g.BellmanFordShortestPaths(startV);

	return 0;
}

void readVertex(Graph& g)
{
	int v;
	std::cin >> v;

	int to;
	float w;
	
	while (std::cin >> to && to != -1)
	{
		std::cin >> w;
		g.addEdge(v, to, w);
	}
}

void printTree(std::vector<std::list<int>>& pathsTree, int startV, int indent)
{
	std::cout << std::setw(static_cast<std::streamsize>(indent)+1) << startV << '\n';
	for (int& i : pathsTree[startV])
	{
		printTree(pathsTree, i, indent + 1);
	}
}
