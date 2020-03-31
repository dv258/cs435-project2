#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.cpp"
#include "graphsearch.cpp"

using namespace std;

Graph<string> createRandomUnweightedGraphIter(int n);
Graph<string> createLinkedList(int n);
vector<Node<string>*> BFTRecLinkedList(Graph<string> graph);
vector<Node<string>*> BFTIterLinkedList(Graph<string> graph);
void printGraph(Graph<string> graph);
template <class T> void printVector(vector<T> &vec);

string randomStringValue(int n);

int main()
{
	//srand(time(NULL));

	Graph<string> graph = createRandomUnweightedGraphIter(16);
	printGraph(graph);

	cout << endl << endl;

	Graph<string> linkgraph = createLinkedList(16);
	printGraph(linkgraph);

	vector<Node<string>*> path = GraphSearch<string>::DFSIter(*linkgraph.getNodeByValue("I6MpsOIB"), *linkgraph.getNodeByValue("iayMcl82"));
	printVector<Node<string>*>(path);

	vector<Node<string>*> traversal = GraphSearch<string>::DFTIter(graph);
	printVector<Node<string>*>(traversal);

	traversal = GraphSearch<string>::BFTIter(graph);
	printVector<Node<string>*>(traversal);

	linkgraph = createLinkedList(10000);

	traversal = BFTRecLinkedList(linkgraph);
	printVector<Node<string>*>(traversal);

	traversal = BFTIterLinkedList(linkgraph);
	printVector<Node<string>*>(traversal);

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

vector<Node<string>*> BFTRecLinkedList(Graph<string> graph)
{
	return GraphSearch<string>::BFTRec(graph);
}

vector<Node<string>*> BFTIterLinkedList(Graph<string> graph)
{
	return GraphSearch<string>::BFTIter(graph);
}

void printGraph(Graph<string> graph)
{
	list<Node<string>*> nodeList = graph.getAllNodes();
	vector<Node<string>*> nodeVec;

	for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++)
		nodeVec.push_back(*iter);

	for (unsigned int i = 0; i < nodeVec.size(); i++)
	{
		printf("%p: %s %3d ", nodeVec[i], nodeVec[i]->value.c_str(), nodeVec[i]->getEdgesCount());

		vector<Node<string>*> nodes = nodeVec[i]->getAdjacentNodes();
		for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
			cout << *iter << " ";

		cout << endl;
	}
}

template <class T>
void printVector(vector<T> &vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}

string randomStringValue(int n)
{
	static string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	string s;

	for (int i = 0; i < n; i++)
		s += charset[rand() % charset.length()];

	return s;
}
