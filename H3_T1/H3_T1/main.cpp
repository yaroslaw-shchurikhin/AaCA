#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <limits>

// ������� ��� ������ ������ ����� �� ����� � ��� ����,
// � ������� ������� � �������
void printTree(std::vector<std::list<int>>& pathsTree, int startV, int indent = 0);

//����� �����
class Graph
{
public:

	//������������
	Graph() = default;
	Graph(int size) { data_.resize(size); }
	~Graph() = default;

	//������� ���������� ����� ����� ���������
	void addEdge(int numSrc, int numDest, float weight)
	{
		data_[numSrc].push_back(std::make_pair<>(numDest, weight));
	}

	//�������� ��������-����� ��� ������� � ������� startV
	std::unique_ptr<std::vector<float>> BellmanFordShortestPaths(int startV)
	{
    //����������� ���� � ������ ���� ��� ����������� ��������� ���� ���� �� 0(E)
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
		//������������� ��� ���� float (����� float < INF)
		constexpr float inf = std::numeric_limits<float>::infinity();

		bool existNegativeCycle = false;
		std::vector<float> d(data_.size(), inf);
		d[startV] = 0.0f;

		std::vector<int> cameFrom(data_.size(), -1);

		//���� �� ���� ������
		for (int i = 0; i < data_.size(); ++i)
		{
			bool isChanges = false;
			for (auto&e : edges)
			{
				//���� �� ������� ���� ���� �����-�� ����, �� ����� ������������� �����
				if (d[e.u] != inf && d[e.u] + e.w < d[e.v])
				{
					isChanges = true;

					//update
					d[e.v] = d[e.u] + e.w;
					if (i == data_.size() - 1) existNegativeCycle = true;

					cameFrom[e.v] = e.u;
				}
			}

			//���� ������ d �� ��������� - ������� �� �����
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

		//������� ����� ����� �� �����
		std::cout << "The weight of a shortest path from vertex " << startV << " to vertex\n";
		std::for_each(d.begin(), d.end(), [](auto& x)
			{
				static int index = 0;
				std::cout << index << "  is  " << x << '\n';

				++index;
			});

		//��������� ������ �����
		std::vector<std::list<int>> pathsTree(data_.size());

		for (int i = 0; i < cameFrom.size(); ++i)
		{
			if (cameFrom[i] != -1) pathsTree[cameFrom[i]].push_back(i);
		}

		//������� ������ ����� �� �����
		std::cout << "\nA shortest paths tree:\n";
		printTree(pathsTree, startV);
		
		return std::make_unique<std::vector<float>>(d);
	}
	
private:

	std::vector<std::list<std::pair<int, float>>> data_;
};

//������� ��� ���������� ������� � ������ � � ���� g
void readVertex(Graph& g);

int main()
{
	//��������� ������, ������� � ��������� �����
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
