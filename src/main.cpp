#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

#include "graph.cpp"
#include "graphsearch.cpp"

using namespace std;

Graph<string> createRandomUnweightedGraphIter(int n);
Graph<string> createLinkedList(int n);
void printGraph(Graph<string> graph);

string randomStringValue(int n);

int main()
{
	//srand(time(NULL));

	Graph<string> graph = createRandomUnweightedGraphIter(7);
	printGraph(graph);

	cout << endl << endl;

	Graph<string> linkgraph = createLinkedList(16);
	printGraph(linkgraph);
/*
	vector<Node<string>*> path = GraphSearch<string>::DFSIter(*linkgraph.getNodeByValue("I6MpsOIB"), *linkgraph.getNodeByValue("iayMcl82"));
	for (unsigned int i = 0; i < path.size(); i++)
		cout << path[i] << " ";
	cout << endl;
*/
	vector<Node<string>*> traversal = GraphSearch<string>::DFTIter(graph);
	for (unsigned int i = 0; i < traversal.size(); i++)
		cout << traversal[i] << " ";
	cout << endl;

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

void printGraph(Graph<string> graph)
{
	list<Node<string>*> nodeList = graph.getAllNodes();
	vector<Node<string>*> nodeVec;

	for (auto iter = nodeList.begin(); iter != nodeList.end(); iter++)
		nodeVec.push_back(*iter);

	for (unsigned int i = 0; i < nodeVec.size(); i++)
	{
		cout << nodeVec[i] << ": " << nodeVec[i]->value << " " << nodeVec[i]->getEdgesCount() << " ";

		for (auto iter = nodeVec[i]->adjacencyMap.begin(); iter != nodeVec[i]->adjacencyMap.end(); iter++)
			cout << iter->second << " ";

		cout << endl;
	}
}

string randomStringValue(int n)
{
	static string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	string s;

	for (int i = 0; i < n; i++)
		s += charset[rand() % charset.length()];

	return s;
}
