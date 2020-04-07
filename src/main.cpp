#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph-api/graph/directedgraph.cpp"
#include "graph-api/graph/graph.cpp"
#include "graph-api/graph/gridgraph.cpp"
#include "graph-api/graph/weightedgraph.cpp"
#include "graph-api/graphsearch.cpp"
#include "graph-api/topsort.cpp"

using namespace std;

Graph<string> createRandomUnweightedGraphIter(int n);
Graph<string> createLinkedList(int n);
DirectedGraph<string> createRandomDAGIter(int n);
WeightedGraph<string> createRandomCompleteWeightedGraph(int n);
WeightedGraph<string> createWeightedLinkedList(int n);
GridGraph<string> createRandomGridGraph(int n);

vector<Node<string>*> BFTRecLinkedList(Graph<string> &graph);
vector<Node<string>*> BFTIterLinkedList(Graph<string> &graph);
unordered_map<string, pair<Node<string>*, int>> dijkstras(Node<string> *start);
vector<GridNode<string>*> astar(GridNode<string> *src, GridNode<string> *dst);

void printGraph(Graph<string> &graph);
void printDotGraph(Graph<string> &graph);
void printDotGraph(GridGraph<string> &graph);
template <class T> void printVector(vector<T> &vec);
template <class T> void printVectorNodes(vector<Node<T>*> &vec);
template <class T> void printVectorNodes(vector<GridNode<T>*> &vec);

string randomStringValue(int n);

int main()
{
	//srand(time(NULL));
	srand(5866);

	Graph<string> unweighted = createRandomUnweightedGraphIter(16);
	cout << "random unweighted" << endl;
	printDotGraph(unweighted);
	cout << endl << endl;

	Graph<string> linkgraph = createLinkedList(16);
	cout << "linked list" << endl;
	printDotGraph(linkgraph);
	cout << endl << endl;

	Node<string> *n1 = linkgraph.getNodeByValue("TIGSiEEh");
	Node<string> *n2 = linkgraph.getNodeByValue("EGebEOcf");

	if(n1 != nullptr && n2 != nullptr)
	{
		vector<Node<string>*> path = GraphSearch<string>::DFSIter(*n1, *n2);
		cout << "DFS of linked list" << endl;
		printVector<Node<string>*>(path);
	}

	vector<Node<string>*> traversal = GraphSearch<string>::DFTIter(unweighted);
	cout << "DFT of random unweighted" << endl;
	printVectorNodes(traversal);

	traversal = GraphSearch<string>::BFTIter(unweighted);
	cout << "BFT of random unweighted" << endl;
	printVectorNodes(traversal);

	linkgraph = createLinkedList(10000);

	traversal = BFTRecLinkedList(linkgraph);
	//printVectorNodes(traversal);
	traversal = BFTIterLinkedList(linkgraph);
	//printVectorNodes(traversal);

	cout << endl << endl;

	DirectedGraph<string> dag = createRandomDAGIter(24);
	cout << "DAG: 24" << endl;
	printDotGraph(dag);

	dag = createRandomDAGIter(1000);
	vector<Node<string>*> topological = TopSort<string>::Kahns(dag);
	//printVectorNodes(topological);
	topological = TopSort<string>::mDFS(dag);
	//printVectorNodes(topological);

	cout << endl << endl;

	WeightedGraph<string> weighted = createRandomCompleteWeightedGraph(5);
	cout << "random complete weighted" << endl;
	printDotGraph(weighted);

	cout << endl << endl;

	n1 = weighted.getNodeByValue("xBTJVOKH");
	if(n1 != nullptr)
	{
		unordered_map<string, pair<Node<string>*, int>> dijkmap = dijkstras(n1);

		cout << "dijkstras of random complete weighted" << endl;
		for (auto pair = dijkmap.begin(); pair != dijkmap.end(); pair++)
			cout << pair->first << " " << pair->second.second << endl;
	}

	cout << endl << endl;

	GridGraph<string> grid = createRandomGridGraph(100);
	GridNode<string> *source = grid.getNodeByValue("0_0");
	GridNode<string> *dest = grid.getNodeByValue("100_100");
	vector<GridNode<string>*> path = astar(source, dest);
	cout << "A* of random grid" << endl;
	printVectorNodes(path);

	return 0;
}

Graph<string> createRandomUnweightedGraphIter(int n)
{
	Graph<string> graph;

	for (int i = 0; i < n; i++)
		graph.addNode(randomStringValue(8));

	list<Node<string>*> nodeList = graph.getAllNodes();
	vector<Node<string>*> nodeVec;

	for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++)
		nodeVec.push_back(*iter);

	for (int i = 0; i < n; i++)
	{
		Node<string> *node = nodeVec[i];
		int edgeCount = rand() % (n + 1);

		while(node->getEdgesCount() < edgeCount)
		{
			Node<string> *adjacentNode = nodeVec[rand() % n];
			graph.addUndirectedEdge(*node, *adjacentNode);
		}
	}

	return graph;
}

Graph<string> createLinkedList(int n)
{
	Graph<string> graph;
	Node<string> *last = nullptr;

	for (int i = 0; i < n; i++)
	{
		Node<string> *node = graph.addNodeReturn(randomStringValue(8));

		if(last != nullptr)
			graph.addUndirectedEdge(*last, *node);
		last = node;
	}

	return graph;
}

DirectedGraph<string> createRandomDAGIter(int n)
{
	DirectedGraph<string> graph;
	int totalNodes = 0;

	vector<Node<string>*> nodes, nextNodes;

	nodes.push_back(graph.addNodeReturn(randomStringValue(8)));
	totalNodes++;

	int minNodes = 0;
	int maxNodes = 2;

	while(totalNodes < n)
	{
		if(!nodes.empty())
		{
			for (unsigned int i = 0; i < nodes.size() && totalNodes < n; i++)
			{
				Node<string> *cur = nodes[i];

				int nodecount = rand() % (maxNodes - minNodes + 1) + minNodes;
				for (int j = 0; j < nodecount && totalNodes < n; j++)
				{
					if(rand() % 100 < 30)
					{
						Node<string> *conn = nullptr;
						for (auto iter = nextNodes.begin(); iter != nextNodes.end(); iter++)
						{
							if(!cur->isConnectedTo(*(*iter)))
							{
								conn = *iter;
								break;
							}
						}

						if(conn != nullptr)
						{
							graph.addDirectedEdge(*cur, *conn);
							continue;
						}
					}

					Node<string> *newNode = graph.addNodeReturn(randomStringValue(8));
					totalNodes++;

					graph.addDirectedEdge(*cur, *newNode);
					nextNodes.push_back(newNode);
				}
			}
		}else
		{
			Node<string> *newNode = graph.addNodeReturn(randomStringValue(8));
			totalNodes++;

			nextNodes.push_back(newNode);
		}

		nodes = nextNodes;
		nextNodes.clear();
	}

	return graph;
}

WeightedGraph<string> createRandomCompleteWeightedGraph(int n)
{
	WeightedGraph<string> graph;

	for (int i = 0; i < n; i++)
		graph.addNode(randomStringValue(8));

	list<Node<string>*> nodeList = graph.getAllNodes();
	vector<Node<string>*> nodeVec;

	for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++)
		nodeVec.push_back(*iter);

	for (int i = 0; i < n; i++)
	{
		Node<string> *node = nodeVec[i];

		for (int j = 0; j < n; j++)
		{
			if(j == i)
				continue;

			Node<string> *adj = nodeVec[j];
			graph.addWeightedEdge(*node, *adj, rand() % 1000);
		}
	}

	return graph;
}

WeightedGraph<string> createWeightedLinkedList(int n)
{
	WeightedGraph<string> graph;
	Node<string> *last = nullptr;

	for (int i = 0; i < n; i++)
	{
		Node<string> *node = graph.addNodeReturn(randomStringValue(8));

		if(last != nullptr)
			graph.addWeightedEdge(*last, *node, 1);
		last = node;
	}

	return graph;
}

GridGraph<string> createRandomGridGraph(int n)
{
	GridGraph<string> graph;

	// (0, 0) top-left

	for (int y = 0; y <= n; y++)
	{
		for (int x = 0; x <= n; x++)
			graph.addGridNode(x, y, to_string(x) + "_" + to_string(y));
	}

	for (int y = 0; y <= n; y++)
	{
		for (int x = 0; x <= n; x++)
		{
			for (int k = 0; k < 4; k++)
			{
				int newx = x;
				int newy = y;

				switch(k)
				{
					case 0:
						newy--;
						break;
					case 1:
						newx++;
						break;
					case 2:
						newy++;
						break;
					case 3:
						newx--;
						break;
				}

				if(newx < 0 || newx > n || newy < 0 || newy > n)
					continue;

				if(rand() % 2)
					graph.addUndirectedEdge(*graph.getNodeByValue(to_string(x) + "_" + to_string(y)), *graph.getNodeByValue(to_string(newx) + "_" + to_string(newy)));
			}
		}
	}

	return graph;
}

vector<Node<string>*> BFTRecLinkedList(Graph<string> &graph)
{
	return GraphSearch<string>::BFTRec(graph);
}

vector<Node<string>*> BFTIterLinkedList(Graph<string> &graph)
{
	return GraphSearch<string>::BFTIter(graph);
}

unordered_map<string, pair<Node<string>*, int>> dijkstras(Node<string> *start)
{
	auto compare = [](pair<Node<string>*, int> lhs, pair<Node<string>*, int> rhs){
		return lhs.second > rhs.second;
	};

	unordered_map<string, pair<Node<string>*, int>> nodeDists;
	unordered_map<string, Node<string>*> visited;
	unordered_map<string, Node<string>*> unvisited;

	nodeDists[start->value] = pair<Node<string>*, int>(start, 0);
	unvisited.insert({start->value, start});

	while(!unvisited.empty())
	{
		priority_queue<pair<Node<string>*, int>, vector<pair<Node<string>*, int>>, decltype(compare)> pq(compare);
		for (auto pair: unvisited)
			pq.push(nodeDists[pair.first]);

		while(!pq.empty())
		{
			Node<string> *node = pq.top().first;
			pq.pop();

			visited.insert({node->value, node});
			unvisited.erase(node->value);

			vector<pair<Node<string>*, int>> adjacents = node->getAdjacentEdges();

			for (unsigned int i = 0; i < adjacents.size(); i++)
			{
				Node<string> *adj = adjacents[i].first;
				int weight = adjacents[i].second;

				if(visited.find(adj->value) != visited.end())
					continue;
				unvisited.insert({adj->value, adj});

				if(nodeDists.find(adj->value) != nodeDists.end())
				{
					if(nodeDists[node->value].second + weight < nodeDists[adj->value].second)
					{
						nodeDists[adj->value].second = nodeDists[node->value].second + weight;
					}
				}else
				{
					nodeDists[adj->value] = pair<Node<string>*, int>(adj, nodeDists[node->value].second + weight);
				}
			}
		}
	}

	return nodeDists;
}

vector<GridNode<string>*> astar(GridNode<string> *src, GridNode<string> *dst)
{
	vector<GridNode<string>*> path;

	auto compare = [](tuple<GridNode<string>*, GridNode<string>*, int, int> lhs, tuple<GridNode<string>*, GridNode<string>*, int, int> rhs){
		return get<2>(lhs) + get<3>(lhs) > get<2>(rhs) + get<3>(rhs);
	};

	//value: node, parent, cost, heuristic
	unordered_map<string, tuple<GridNode<string>*, GridNode<string>*, int, int>> nodeDists;
	unordered_map<string, GridNode<string>*> visited;
	unordered_map<string, GridNode<string>*> unvisited;

	nodeDists[src->value] = tuple<GridNode<string>*, GridNode<string>*, int, int>(src, nullptr, 0, 0);
	unvisited.insert({src->value, src});

	while(!unvisited.empty())
	{
		priority_queue<tuple<GridNode<string>*, GridNode<string>*, int, int>, vector<tuple<GridNode<string>*, GridNode<string>*, int, int>>, decltype(compare)> pq(compare);
		for (auto tup: unvisited)
			pq.push(nodeDists[tup.first]);

		while(!pq.empty())
		{
			GridNode<string> *node = get<0>(pq.top());
			pq.pop();

			visited.insert({node->value, node});
			unvisited.erase(node->value);

			if(node == dst)
			{
				unvisited.clear();
				break;
			}

			vector<pair<GridNode<string>*, int>> adjacents = node->getAdjacentEdges();

			for (unsigned int i = 0; i < adjacents.size(); i++)
			{
				GridNode<string> *adj = adjacents[i].first;
				int weight = adjacents[i].second;

				if(visited.find(adj->value) != visited.end())
					continue;
				unvisited.insert({adj->value, adj});

				if(nodeDists.find(adj->value) != nodeDists.end())
				{
					if(get<2>(nodeDists[node->value]) + weight < get<2>(nodeDists[adj->value]))
					{
						get<1>(nodeDists[adj->value]) = node;
						get<2>(nodeDists[adj->value]) = get<2>(nodeDists[node->value]) + weight;
						get<3>(nodeDists[adj->value]) = adj->getDistance(*dst);
					}
				}else
				{
					nodeDists[adj->value] = tuple<GridNode<string>*, GridNode<string>*, int, int>(adj, node, get<2>(nodeDists[node->value]) + weight, adj->getDistance(*dst));
				}
			}
		}
	}

	for (GridNode<string> *node = get<0>(nodeDists[dst->value]); node != nullptr; node = get<1>(nodeDists[node->value]))
		path.push_back(node);

	reverse(path.begin(), path.end());

	return path;
}

void printGraph(Graph<string> &graph)
{
	list<Node<string>*> nodeList = graph.getAllNodes();

	for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++)
	{
		Node<string> *node = *iter;
		printf("%p: %s %3d ", node, node->value.c_str(), node->getEdgesCount());

		vector<Node<string>*> children = node->getAdjacentNodes();
		for (auto iterch = children.begin(); iterch != children.end(); iterch++)
			cout << *iterch << " ";

		cout << endl;
	}
}

void printDotGraph(Graph<string> &graph)
{
	list<Node<string>*> nodeList = graph.getAllNodes();

	cout << "digraph {" << endl;

	for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++)
	{
		Node<string> *node = *iter;
		//vector<Node<string>*> children = node->getAdjacentNodes();
		vector<pair<Node<string>*, int>> children = node->getAdjacentEdges();

		if(children.size() > 0)
		{
			for (auto iterch = children.begin(); iterch != children.end(); iterch++)
			{
				Node<string> *child = iterch->first;
				int weight = iterch->second;

				cout << "  " << node->value << " -> " << child->value << " [label=\"" << weight << "\"];" << endl;
			}
		}else
		{
			cout << "  " << node->value << ";" << endl;
		}
	}

	cout << "}" << endl;
}

template <class T>
void printVector(vector<T> &vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}

template <class T>
void printVectorNodes(vector<Node<T>*> &vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
		cout << vec[i]->value << " ";
	cout << endl;
}

template <class T>
void printVectorNodes(vector<GridNode<T>*> &vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
		cout << vec[i]->value << " ";
	cout << endl;
}

string randomStringValue(int n)
{
	static string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string s;

	for (int i = 0; i < n; i++)
		s += charset[rand() % charset.length()];

	return s;
}
