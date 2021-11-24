#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

//����� �����
class Graph
{
public:

	//������������
	Graph() = default;
	Graph(int size) { data_.resize(size); }
	~Graph() = default;

	decltype(auto) size() { return data_.size(); }
	std::list<std::pair<int, int>>& operator[](const size_t index) { return data_[index]; }

	//������� ���������� ����� ����� ���������
	void addEdge(int numSrc, int numDest, float weight)
	{
		data_[numSrc].push_back(std::make_pair<>(numDest, weight));
	}

private:

	std::vector<std::list<std::pair<int, int>>> data_;
};

//������� ��� ���������� ������� � ������ � � ���� g
void readVertex(Graph& g);
bool checkShortestPathsArray(int startV, std::vector<int>& shortestPaths, Graph& g);

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

	std::vector<int> a(size);
	for (int i = 0; i < size; ++i) std::cin >> a[i];

	bool isShortestPaths = checkShortestPathsArray(startV, a, g);

	if (isShortestPaths) std::cout << "\nThis is array of shortest paths";
	else std::cout << "\nThis is not array of shortest paths";

	return 0;
}

void readVertex(Graph& g)
{
	int v;
	std::cin >> v;

	int to;
	int w;

	while (std::cin >> to && to != -1)
	{
		std::cin >> w;
		g.addEdge(v, to, w);
	}
}

bool checkShortestPathsArray(int startV, std::vector<int>& shortestPaths, Graph& g)
{
	if (shortestPaths[startV] != 0) return false;

	//����������� ���� � ������ ���� ��� ����������� ��������� ���� ���� �� 0(E)
	struct Edge
	{
		int u, v;
		int w;
	};
	std::list<Edge> edges;

	for (int i = 0; i < g.size(); ++i)
	{
		for (auto& j : g[i])
		{

			edges.push_back(Edge{ i, j.first, j.second });
		}
	}

	//������������� ��� ���� float (����� float < INF)
	constexpr float inf = std::numeric_limits<float>::infinity();

	// �������� �������������� ��������-�����
	for (auto& e : edges)
	{
		if (shortestPaths[e.u] != inf && shortestPaths[e.u] + e.w < shortestPaths[e.v])
		{
			return false;
		}
	}

	return true;
}
