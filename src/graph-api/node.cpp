#ifndef __NODE_H
#define __NODE_H

#include <unordered_map>
#include <vector>

using namespace std;

template <class T>
class Node
{
private:
	unordered_map<T, pair<Node<T>*, int>> adjacencyMap;

public:
	T value;

	Node(T value)
	{
		this->value = value;
	}

	void addDirectedEdge(Node<T> &node)
	{
		this->addWeightedEdge(node, 0);
	}

	void addWeightedEdge(Node<T> &node, int weight)
	{
		this->adjacencyMap.insert({node.value, pair<Node<T>*, int>(&node, weight)});
	}

	void addUndirectedEdge(Node<T> &node)
	{
		this->addDirectedEdge(node);
		node.addDirectedEdge(*this);
	}

	void removeDirectedEdge(Node<T> &node)
	{
		this->adjacencyMap.erase(node.value);
	}

	void removeUndirectedEdge(Node<T> &node)
	{
		this->removeDirectedEdge(node);
		node.removeDirectedEdge(*this);
	}

	bool isConnectedTo(Node<T> &node)
	{
		return this->adjacencyMap.find(node.value) != this->adjacencyMap.end();
	}

	vector<Node<T>*> getAdjacentNodes()
	{
		vector<Node<T>*> nodes;

		for (auto iter = this->adjacencyMap.begin(); iter != this->adjacencyMap.end(); iter++)
			nodes.push_back(iter->second.first);

		return nodes;
	}

	vector<pair<Node<T>*, int>> getAdjacentEdges()
	{
		vector<pair<Node<T>*, int>> nodes;

		for (auto iter = this->adjacencyMap.begin(); iter != this->adjacencyMap.end(); iter++)
			nodes.push_back(iter->second);

		return nodes;
	}

	int getEdgesCount()
	{
		return this->adjacencyMap.size();
	}

	bool operator==(const Node<T> &other) const
	{
		return this->value == other.value;
	}

	bool operator!=(const Node<T> &other) const
	{
		return this->value != other.value;
	}
};

#endif //#ifndef __NODE_H
