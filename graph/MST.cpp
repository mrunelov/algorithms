//
// @authors:
// Martin Runelöv
// Philip Sköld
//


#include "MST.h"
#include "UnionFind.h"

vector<edge> MinimumSpanningTree(graph G)
{
	vector<edge> mst;
	UnionFind U(G.N);
	vector<edge> edges = G.E;
	sort(edges.begin(), edges.end(), [](edge a, edge b){ return a.w < b.w; });

	trav(e, edges)
	{
		int from = (*e).from;
		int to = (*e).to;
		if (!U.InSame(from, to))
		{
			int w = (*e).w;
			if (from < to)
				mst.push_back(edge(from,to,w));
			else 
				mst.push_back(edge(to,from,w));
			U.Union(from, to);
		}
	}

	bool isforest = false;
	int s = U.Find(0);
	rep(i, 1, G.N)
	{
		if (U.Find(i) != s)
		{
			isforest = true;
			break;
		}
	}

	if (!isforest)
	{
		return mst;
	}
	else
	{
		return vector<edge>();
	}
}
