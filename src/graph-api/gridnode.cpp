#ifndef __GRIDNODE_H
#define __GRIDNODE_H

#include <unordered_map>
#include <vector>

#include <math.h>

#include "node.cpp"

using namespace std;

template <class T>
class GridNode : public Node<T>
{
	unordered_map<T, pair<GridNode<T>*, int>> adjacencyMap;

	int x;
	int y;

public:
	GridNode(int x, int y, T value) : Node<T> { value }
	{
		this->x = x;
		this->y = y;
	}

	void addDirectedEdge(GridNode<T> &node)
	{
		this->addWeightedEdge(node, 0);
	}

	void addWeightedEdge(GridNode<T> &node, int weight)
	{
		this->adjacencyMap.insert({node.value, pair<GridNode<T>*, int>(&node, weight)});
	}

	void addUndirectedEdge(GridNode<T> &node)
	{
		if((this->y == node.y && (this->x + 1 == node.x || this->x - 1 == node.x)) || (this->x == node.x && (this->y + 1 == node.y || this->y - 1 == node.y)))
		{
			this->addDirectedEdge(node);
			node.addDirectedEdge(*this);
		}
	}

	void removeDirectedEdge(GridNode<T> &node)
	{
		this->adjacencyMap.erase(node.value);
	}

	void removeUndirectedEdge(GridNode<T> &node)
	{
		this->removeDirectedEdge(node);
		node.removeDirectedEdge(*this);
	}

	bool isConnectedTo(GridNode<T> &node)
	{
		return this->adjacencyMap.find(node.value) != this->adjacencyMap.end();
	}

	vector<GridNode<T>*> getAdjacentNodes()
	{
		vector<GridNode<T>*> nodes;

		for (auto iter = this->adjacencyMap.begin(); iter != this->adjacencyMap.end(); iter++)
			nodes.push_back(iter->second.first);

		return nodes;
	}

	vector<pair<GridNode<T>*, int>> getAdjacentEdges()
	{
		vector<pair<GridNode<T>*, int>> nodes;

		for (auto iter = this->adjacencyMap.begin(); iter != this->adjacencyMap.end(); iter++)
			nodes.push_back(iter->second);

		return nodes;
	}

	int getDistance(GridNode<T> &node)
	{
		return abs(node.x - this->x) + abs(node.y - this->y);
	}

	int getEdgesCount()
	{
		return this->adjacencyMap.size();
	}

	bool operator==(const GridNode<T> &other) const
	{
		return this->value == other.value;
	}

	bool operator!=(const GridNode<T> &other) const
	{
		return this->value != other.value;
	}
};

#endif //#ifndef __GRIDNODE_H
