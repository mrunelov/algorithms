//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "dijkstras.h"

vector<int> dist; // min pathlengths from single source for each node.

struct Cmp 
{
	bool operator() (int n1, int n2) const 
	{
		if (dist[n1] != dist[n2])
			return dist[n1] < dist[n2];
		return n1 > n2;
	}
};

int reachableAt(edge e, int t) 
{
	if (e.P == 0) { // special case. can only use edge once at time e.t
		if(t > e.t) 
			return -1;
		if (t == e.t)
			return 0;
	}
	if (t < e.t) return e.t-t; // we haven't reached the starting time yet.

	// The last modulo e.P is only used when we get (t-e.t)%e.P == e.P,
	// to return 0 instead of e.P - 0 = e.P.
	return (e.P - ((t-e.t)%e.P))%e.P; // wait depending on time left until a multiple of e.P after e.t
}

vector<int> dijkstras_ss(graph& G, int start)
{
	dist.clear();
	dist.resize(G.N, INT_MAX);
	vector<int> parent(G.N, -1); // parent vector that can be traversed to construct paths
	parent[start] = -1;
	dist[start] = 0;
	set<int, Cmp> q;
	q.insert(start);
	while (!q.empty())
	{
		int u = *q.begin(); // top/front
		q.erase(q.begin()); // pop

		vector<edge> adjacent = G.getAdj(u);
		rep(i, 0, adjacent.size())
		{
			int d = dist[u] + adjacent[i].w;
			int v = adjacent[i].to;
			if (d < dist[v]) 
			{
				if (q.count(v))
					q.erase(v);
				dist[v] = d;
				parent[v] = u;
				q.insert(v);
			}
		}
	}
	return dist;
	// return parent; // paths;
}


vector<int> dijkstras_ss_tt(graph& G, int start) 
{
	dist.clear();
	dist.resize(G.N, INT_MAX);
	vector<int> parent(G.N, -1); // parent vector that can be traversed to construct paths
	parent[start] = -1;
	dist[start] = 0;
	set<int, Cmp> q;
	q.insert(start);
	while (!q.empty())
	{
		int u = *q.begin(); // top/front
		q.erase(q.begin()); // pop

		vector<edge> adjacent = G.getAdj(u);
		rep(i, 0, adjacent.size())
		{
			int wait = reachableAt(adjacent[i], dist[u]);
			if (wait == -1) // can't visit anymore
				continue;
			int d = dist[u] + adjacent[i].w + wait;
			int v = adjacent[i].to;
			if (d < dist[v]) 
			{
				if (q.count(v))
					q.erase(v);
				dist[v] = d;
				parent[v] = u;
				q.insert(v);
			}
		}
	}
	return dist; // 
	// return parent; // see documentation in header;	
}

