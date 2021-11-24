#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using graph = std::vector<std::list<int>>;

std::vector<bool> visited;
std::vector<int> order;
std::list<int> component;

//Support methods
void readVertex(graph& g);
graph reverseGraph(graph& g);
int checkSCC(graph& scc, int v);
void createEdge(graph& g, int v1, int v2);
void printGraph(graph& g);

//Main methods
void dfs1(graph& or_graph, int v);
void dfs2(graph& trans_graph, int v);
std::pair<graph, std::vector<int>> getSCC(graph& g);
graph getMetaGraph(graph& g);

int main()
{
	size_t size;
	std::cin >> size;

	graph orient_graph(size);

	visited.resize(size);
	order.resize(size);

	for (int i = 0; i < size; ++i)
	{
		readVertex(orient_graph);
	}

	std::cout << '\n';
	graph result = getMetaGraph(orient_graph);

	std::cout << "\nMeta-graph:\n";
	printGraph(result);

	return 0;
}

void readVertex(graph& g)
{
	int v;
	std::cin >> v;

	int to;
	while (std::cin >> to && to != -1)
	{
		g[v].push_back(to);
	}
}

graph reverseGraph(graph& g)
{
	graph reversed(g.size());

	for (int v = 0; v < g.size(); ++v)
	{
		for (auto& to : g[v])
		{
			reversed[to].push_back(v);
		}
	}

	return reversed;
}

int checkSCC(graph& scc, int v)
{
	for(int i = 0; i < scc.size(); ++i)
	{
		for (auto j : scc[i])
		{
			if (v == j) return i;
		}
	}

	return false;
}

void createEdge(graph& g, int src, int dest)
{
	g[src].push_back(dest);
}

void printGraph(graph& g)
{
	for (int i = 0; i < g.size(); ++i)
	{
		std::cout << i << "   ";

		for (int j : g[i])
		{
			std::cout << j << ' ';
		}
		std::cout << "  " << -1 << '\n';
	}
}

void dfs1(graph& or_graph, int v)
{
	visited[v] = true;

	for (int i : or_graph[v])
	{
		if (!visited[i]) dfs1(or_graph, i);
	}

	order.push_back(v);
}

void dfs2(graph& trans_graph, int v)
{
	visited[v] = true;
	component.push_back(v);

	for (int i : trans_graph[v])
	{
		if (!visited[i]) dfs2(trans_graph, i);
	}

	order.push_back(v);
}

std::pair<graph, std::vector<int>> getSCC(graph& g)
{
	graph transponsed = reverseGraph(g);
	graph scc;
	std::vector<int> sccNumbers(g.size());

	visited.assign(visited.size(), false);
	for (int i = 0; i < g.size(); ++i)
	{
		if (!visited[i]) dfs1(g, i);
	}

	visited.assign(visited.size(), false);
	std::reverse(order.begin(), order.end());

	int count_SCC = 0;
	for (int i = 0; i < g.size(); ++i)
	{
		if (!visited[order[i]])
		{
			dfs2(transponsed, order[i]);

			std::cout << "SCC " << count_SCC << ": ";
			std::for_each(component.begin(), component.end(), 
				[&](int x) {
					std::cout << x << ' ';
					sccNumbers[x] = count_SCC;
				});

			std::cout << '\n';

			scc.push_back(component);
			component.clear();
			++count_SCC;
		}
	}
	return std::make_pair<>(scc, sccNumbers);
}

graph getMetaGraph(graph& g)
{
	auto scc_info = getSCC(g);
	graph metaGraph(scc_info.first.size());

	std::vector<bool> scc_visited(scc_info.first.size());
	scc_visited.assign(scc_visited.size(), false);

	for (int i = 0; i < scc_info.first.size(); ++i)
	{
		for (int j : scc_info.first[i])
		{
			for (int k : g[j])
			{
				if (scc_info.second[k] != i && !scc_visited[scc_info.second[k]])
				{
					createEdge(metaGraph, i, scc_info.second[k]);
					scc_visited[scc_info.second[k]] = true;
				}
			}
		}

		//scc_visited.assign(scc_visited.size(), false);
		for (auto n : metaGraph[i])
		{
			scc_visited[n] = false;
		}
	}

	return metaGraph;
}
