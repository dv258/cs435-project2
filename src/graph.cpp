#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <list>
#include <unordered_map>

#include "node.cpp"

using namespace std;

template <class T>
class Graph
{
	unordered_map<T, Node<T>*> nodeMap;
public:
	Graph(){}

	void addNode(T value)
	{
		this->addNodeReturn(value);
	}

	Node<T> *addNodeReturn(T value)
	{
		Node<T> *node = new Node<T>(value);
		this->nodeMap.insert({value, node});
		return node;
	}

	Node<T> *getNodeByValue(T value)
	{
		auto node = this->nodeMap.find(value);
		return node != this->nodeMap.end() ? node->second : nullptr;
	}

	void addUndirectedEdge(Node<T> &first, Node<T> &second)
	{
		first.addUndirectedEdge(second);
	}

	void removeUndirectedEdge(Node<T> &first, Node<T> &second)
	{
		first.removeUndirectedEdge(second);
	}

	list<Node<T>*> getAllNodes()
	{
		list<Node<T>*> nodeList;
		for (const auto &pair : this->nodeMap)
			nodeList.push_back(pair.second);

		return nodeList;
	}

	int getNodeCount()
	{
		return this->nodeMap.size();
	}
};

#endif //#ifndef __GRAPH_H
