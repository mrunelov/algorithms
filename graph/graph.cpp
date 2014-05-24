//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "graph.h"

//
// NODE
//

void node::add(edge e) 
{
	adj.push_back(e);

}

//
// GRAPH
//

graph::graph()
{
}

graph::graph(int N)
	: N(N)
{
	V.resize(N);
}

node& graph::getNode(int idx)
{
	// assert(idx < N);
	return V[idx];
}

vector<edge>& graph::getAdj(int node)
{
	return getNode(node).adj;
}

void graph::addEdge(int from, int to)
{
	edge e(from,to);
	++V[from].outDeg; // eulerian stuff
	++V[to].inDeg;
	e.idx = E.size();
	V[from].add(e);
	E.push_back(e);
}

void graph::addEdge(int from, int to, int w)
{
	edge e(from,to,w);
 	V[from].add(e);
	E.push_back(e);
}

void graph::addEdge(int from, int to, int w, int t, int P) 
{
	edge e(from,to,w,t,P);
	V[from].add(e);
	E.push_back(e);
}


int graph::getWeight(int from, int to)
{
	trav(e, getNode(from).adj)
	{
		if ((*e).to == to)
			return (*e).w;
	}
	return -1;
}


vector<int> graph::getPath(vector<int>& parent, int start, int end) 
{
	vector<int> path;
	int last = end;
	while(last != -1) {
		path.push_back(last);
		last = parent[last]; 
	}
	if (path[path.size()-1] != start) // unreachable
		return vector<int>();
	reverse(path.begin(),path.end());
	return path;
}

int graph::getPathLength(const vector<int>& path)
{
	int res = 0;
	if (path.empty())
		return -1;

	if (path.size() >= 2)
	{
		rep(i, 0, path.size()-1)
		{
			res += getWeight(path[i], path[i + 1]);
		}
	}
	return res;
}

graph::~graph()
{
}
