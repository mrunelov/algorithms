#include "FloydWarshall.h"

t_FW FloydWarshall(graph& G)
{

	t_distancematrix dist(G.N, vector<int>(G.N, FW_INF));
	vector<vector<int>> next(G.N, vector<int>(G.N, FW_NULLNODE));

	//base cases
	rep(v, 0, G.N)
	{
		dist[v][v] = 0;
		//next[v][v] = v;
	}

	rep(n, 0, G.N)
	{
		trav(e, G.getAdj(n))
		{
			int u = n;
			int v = (*e).to;

			if (u == v) {
				dist[u][v] = (*e).w >= 0 ? 0 : (*e).w; //if u == v set dist <= 0
			}
			else
				dist[u][v] = (*e).w;
		}
	}

	//floyd warshall
	rep(i, 0, G.N)
	{
		rep(j, 0, G.N)
		{
			rep(k, 0, G.N)
			{
				if (dist[j][i] != FW_INF && dist[i][k] != FW_INF) {
					if (dist[j][i] + dist[i][k] < dist[j][k])
					{
						dist[j][k] = dist[j][i] + dist[i][k];
						next[j][k] = next[j][i];
					}
				}
			}
		}
	}
	return make_pair(dist, next);
}


int pathlength(t_FW& fw, int u, int v)
{
	t_distancematrix& dist = fw.first;
	t_nextmatrix& next = fw.second;

	//find negative cycles
	function<int(int, int)> path = [&](int i, int j)
	{
		if (dist[i][j] == FW_INF)
			return FW_INF;

		if (dist[i][i] < 0 || dist[j][j] < 0 || dist[i][j] == FW_NEGINF)
			return FW_NEGINF;

		//path is calculated as: path(i, next[i][j]) -> path(next[i][j], j)
		int intermediate = next[i][j];
		if (intermediate == FW_NULLNODE) {
			return 0; // i->j is the shortest path
		} 
		
		int seg1 = path(i, intermediate);
		int seg2 = path(intermediate, j);
		
		if (seg1 == FW_INF || seg2 == FW_INF)
			return FW_INF;

		if (seg1 == FW_NEGINF || seg2 == FW_NEGINF)
			return FW_NEGINF;

		return 0;
		
	};

	int result = path(u, v);

	return (result == 0) ? dist[u][v] : result; //if res is 0, then return INF or NEGINF
}
