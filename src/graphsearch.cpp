#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

#include "graph.cpp"

using namespace std;

template <class T>
class GraphSearch
{
public:
	static vector<Node<T>*> DFSIter(Node<T> &start, Node<T> &end)
	{
		vector<Node<T>*> path;
		//key: node value, value: {node, parent}
		unordered_map<T, pair<Node<T>*, Node<T>*>> visited;
		stack<Node<T>*> stack;

		stack.push(&start);

		while(!stack.empty())
		{
			Node<T> *cur = stack.top();
			stack.pop();

			if(*cur == end)
			{
				//traverse back up the visited parent-child list
				for (Node<T> *child = visited[cur->value].first; *child != start; child = visited[child->value].second)
					path.push_back(child);
				path.push_back(&start);
				break;
			}

			for (auto iter = cur->adjacencyMap.begin(); iter != cur->adjacencyMap.end(); iter++)
			{
				Node<T> *adj = iter->second;

				if(visited.find(adj->value) != visited.end())
					continue;
				visited.insert({adj->value, pair<Node<T>*, Node<T>*>(adj, cur)});

				stack.push(adj);
			}
		}

		reverse(path.begin(), path.end());
		return path;
	}

	static vector<Node<T>*> DFSRec(Node<T> &start, Node<T> &end)
	{
		vector<Node<T>*> path;
		unordered_map<T, Node<T>*> visited;
		bool found = false;

		GraphSearch::_DFSRec(start, end, path, visited, found);
		reverse(path.begin(), path.end());

		return path;
	}

	static vector<Node<T>*> BFTIter(Graph<T> &graph)
	{
		vector<Node<T>*> traversal;
		list<Node<T>*> nodeList = graph.getAllNodes();
		unordered_map<T, Node<T>*> visited;
		queue<Node<T>*> queue;

		for (auto nlIter = nodeList.begin(); nlIter != nodeList.end() && nodeList.size() > traversal.size(); nlIter++)
		{
			Node<T> *nlcur = *nlIter;

			if(visited.find(nlcur->value) != visited.end())
				continue;

			queue.push(nlcur);

			while(!queue.empty())
			{
				Node<T> *cur = queue.front();
				queue.pop();

				if(visited.find(cur->value) != visited.end())
					continue;
				visited.insert({cur->value, cur});

				traversal.push_back(cur);

				for (auto iter = cur->adjacencyMap.begin(); iter != cur->adjacencyMap.end(); iter++)
				{
					Node<T> *adj = iter->second;
					queue.push(adj);
				}
			}
		}

		return traversal;
	}

	static vector<Node<T>*> DFTIter(Graph<T> &graph)
	{
		vector<Node<T>*> traversal;
		list<Node<T>*> nodeList = graph.getAllNodes();
		unordered_map<T, Node<T>*> visited;
		stack<Node<T>*> stack;

		for (auto nlIter = nodeList.begin(); nlIter != nodeList.end() && nodeList.size() > traversal.size(); nlIter++)
		{
			Node<T> *nlcur = *nlIter;

			if(visited.find(nlcur->value) != visited.end())
				continue;

			stack.push(nlcur);

			while(!stack.empty())
			{
				Node<T> *cur = stack.top();
				stack.pop();

				if(visited.find(cur->value) != visited.end())
					continue;
				visited.insert({cur->value, cur});

				traversal.push_back(cur);

				for (auto iter = cur->adjacencyMap.begin(); iter != cur->adjacencyMap.end(); iter++)
				{
					Node<T> *adj = iter->second;
					stack.push(adj);
				}
			}
		}

		return traversal;
	}
private:
	static void _DFSRec(Node<T> &cur, Node<T> &end, vector<Node<T>*> &path, unordered_map<T, Node<T>*> &visited, bool &found)
	{
		visited.insert({cur.value, &cur});

		if(cur == end)
		{
			path.push_back(&cur);
			found = true;
			return;
		}

		for (auto iter = cur.adjacencyMap.begin(); iter != cur.adjacencyMap.end(); iter++)
		{
			Node<T> *adj = iter->second;

			if(visited.find(adj->value) != visited.end())
				continue;

			GraphSearch::_DFSRec(*adj, end, path, visited, found);

			if(found)
			{
				path.push_back(&cur);
				return;
			}
		}
	}
};