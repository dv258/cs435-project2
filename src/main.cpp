#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "directedgraph.cpp"
#include "graph.cpp"
#include "graphsearch.cpp"
#include "topsort.cpp"

using namespace std;

Graph<string> createRandomUnweightedGraphIter(int n);
Graph<string> createLinkedList(int n);
DirectedGraph<string> createRandomDAGIter(int n);
vector<Node<string>*> BFTRecLinkedList(Graph<string> &graph);
vector<Node<string>*> BFTIterLinkedList(Graph<string> &graph);
void printGraph(Graph<string> &graph);
void printDotGraph(Graph<string> &graph);
template <class T> void printVector(vector<T> &vec);
template <class T> void printVectorNodes(vector<Node<T>*> &vec);

string randomStringValue(int n);

int main()
{
	//srand(time(NULL));
	srand(5865);

	Graph<string> graph = createRandomUnweightedGraphIter(16);
	printDotGraph(graph);
	cout << endl << endl;

	Graph<string> linkgraph = createLinkedList(16);
	printDotGraph(linkgraph);
	cout << endl;

	Node<string> *n1 = linkgraph.getNodeByValue("TIGSiEEh");
	Node<string> *n2 = linkgraph.getNodeByValue("EGebEOcf");

	if(n1 != nullptr && n2 != nullptr)
	{
		vector<Node<string>*> path = GraphSearch<string>::DFSIter(*n1, *n2);
		printVector<Node<string>*>(path);
	}

	vector<Node<string>*> traversal = GraphSearch<string>::DFTIter(graph);
	printVector<Node<string>*>(traversal);

	traversal = GraphSearch<string>::BFTIter(graph);
	printVector<Node<string>*>(traversal);

	linkgraph = createLinkedList(10000);

	traversal = BFTRecLinkedList(linkgraph);
	//printVectorNodes(traversal);
	traversal = BFTIterLinkedList(linkgraph);
	//printVectorNodes(traversal);

	DirectedGraph<string> dag = createRandomDAGIter(24);
	printDotGraph(dag);

	dag = createRandomDAGIter(1000);
	vector<Node<string>*> topological = TopSort<string>::Kahns(dag);
	//printVectorNodes(topological);
	topological = TopSort<string>::mDFS(dag);
	//printVectorNodes(topological);

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
			node->addUndirectedEdge(*adjacentNode);
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
			for (int i = 0; i < nodes.size() && totalNodes < n; i++)
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

vector<Node<string>*> BFTRecLinkedList(Graph<string> &graph)
{
	return GraphSearch<string>::BFTRec(graph);
}

vector<Node<string>*> BFTIterLinkedList(Graph<string> &graph)
{
	return GraphSearch<string>::BFTIter(graph);
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
		vector<Node<string>*> children = node->getAdjacentNodes();

		if(children.size() > 0)
		{
			for (auto iterch = children.begin(); iterch != children.end(); iterch++)
			{
				Node<string> *child = *iterch;
				cout << "  " << node->value << " -> " << child->value << ";" << endl;
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

string randomStringValue(int n)
{
	static string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string s;

	for (int i = 0; i < n; i++)
		s += charset[rand() % charset.length()];

	return s;
}
