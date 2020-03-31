#ifndef __NODE_H
#define __NODE_H

#include <unordered_map>

using namespace std;

template <class T>
class Node
{
public:
	T value;
	unordered_map<T, Node<T>*> adjacencyMap;

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
