#ifndef __NODE_H
#define __NODE_H

#include <unordered_map>
#include <vector>

using namespace std;

template <class T>
class Node
{
private:
	unordered_map<T, Node<T>*> adjacencyMap;

public:
	T value;

	Node(T value)
	{
		this->value = value;
	}

	void addDirectedEdge(Node<T> &node)
	{
		this->adjacencyMap.insert({node.value, &node});
	}

	void addUndirectedEdge(Node<T> &node)
	{
		this->addDirectedEdge(node);
		node.addDirectedEdge(*this);
	}

	void removeDirectedEdge(Node<T> &node)
	{
		this->adjacencyList.erase(node.value);
	}

	void removeUndirectedEdge(Node<T> &node)
	{
		this->removeDirectedEdge(node);
		node.removeDirectedEdge(*this);
	}

	vector<Node<T>*> getAdjacentNodes()
	{
		vector<Node<T>*> nodes;

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
