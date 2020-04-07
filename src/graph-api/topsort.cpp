#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

#include "graph/directedgraph.cpp"

using namespace std;

template <class T>
class TopSort
{
public:
	static vector<Node<T>*> Kahns(DirectedGraph<T> &graph)
	{
		vector<Node<T>*> topo;
		unordered_map<T, int> indegree;
		list<Node<T>*> nodes = graph.getAllNodes();

		for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
			indegree[(*iter)->value] = 0;

		for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
		{
			Node<T> *node = *iter;
			vector<Node<T>*> children = node->getAdjacentNodes();

			for (unsigned int i = 0; i < children.size(); i++)
			{
				Node<T> *child = children[i];
				indegree[child->value]++;
			}
		}

		queue<Node<T>*> queue;
		for (auto pair = indegree.begin(); pair != indegree.end(); pair++)
		{
			if(pair->second == 0)
				queue.push(graph.getNodeByValue(pair->first));
		}

		while(!queue.empty())
		{
			Node<T> *node = queue.front();
			topo.push_back(node);
			queue.pop();

			vector<Node<T>*> children = node->getAdjacentNodes();

			for (unsigned int i = 0; i < children.size(); i++)
			{
				indegree[children[i]->value]--;
				if(indegree[children[i]->value] == 0)
					queue.push(children[i]);
			}
		}

		return topo;
	}

	static vector<Node<T>*> mDFS(DirectedGraph<T> &graph)
	{
		vector<Node<T>*> topo;
		unordered_map<T, Node<T>*> visited;
		stack<Node<T>*> stack;

		list<Node<T>*> nodes = graph.getAllNodes();

		for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
		{
			if(visited.find((*iter)->value) == visited.end())
				TopSort<T>::_mDFS(*iter, visited, stack);
		}

		while(!stack.empty())
		{
			topo.push_back(stack.top());
			stack.pop();
		}

		return topo;
	}
private:
	static void _mDFS(Node<T> *node, unordered_map<T, Node<T>*> &visited, stack<Node<T>*> &stack)
	{
		visited.insert({node->value, node});

		vector<Node<T>*> children = node->getAdjacentNodes();
		for (unsigned int i = 0; i < children.size(); i++)
		{
			Node<T> *adj = children[i];
			if(visited.find(adj->value) != visited.end())
				continue;

			TopSort<T>::_mDFS(adj, visited, stack);
		}

		stack.push(node);
	}
};
