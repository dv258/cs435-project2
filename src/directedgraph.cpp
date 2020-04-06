#ifndef __DIRECTEDGRAPH_H
#define __DIRECTEDGRAPH_H

#include <iostream>
#include <list>
#include <unordered_map>

#include "graph.cpp"
#include "node.cpp"

using namespace std;

template <class T>
class DirectedGraph : public Graph<T>
{
public:
	DirectedGraph(){}

	void addDirectedEdge(Node<T> &first, Node<T> &second)
	{
		first.addDirectedEdge(second);
	}

	void removeDirectedEdge(Node<T> &first, Node<T> &second)
	{
		first.removeDirectedEdge(second);
	}
};

#endif //#ifndef __DIRECTEDGRAPH_H
