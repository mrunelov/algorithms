//
// @authors:
// Martin Runelöv
// Philip Sköld
//

//
// Includes
//

#include "common.h"
#include "graph.h"
#include "dijkstras.h"
#include "FloydWarshall.h"
#include "MST.h"
#include "EulerianPath.h"
#include "EdmondsKarp.h"
#include "FlowGraph.h"

#ifdef WINDOWS
#include <cstdlib>
#endif

//
// Lab 2
//

// KATTIS input/output functions
void KATTISshortestPathNonNegative();
void KATTISshortestPathTimeTable();
void KATTISFloydWarshall();
void KATTIS_MST();
void KATTIS_MaxFlow();
void KATTIS_EulerianPath();

int main() {
	// OBS only one active at a time
	// KATTISshortestPathNonNegative();
	// KATTISshortestPathTimeTable();
	// KATTISFloydWarshall();
	// KATTIS_MST();
	// KATTIS_EulerianPath();
	KATTIS_MaxFlow();
	return 0;
}


void KATTISshortestPathNonNegative()
{
	vector<int> path;
	while (true)
	{
		int N, m, q, start;
		//scanf("%d%d%d%d", &N, &m, &q, &start);
		cin >> N >> m >> q >> start;

		if (N == 0 && m == 0 && q == 0 && start == 0)
			break;

		graph G(N);
		int to, from, w;
		rep(i, 0, m)
		{
			scanf("%d%d%d", &from, &to, &w);
			G.addEdge(from, to, w);
		}

		// vector<int> parent = dijkstras_ss(G, start); // reconstruct paths from parents with graph::getPath
		vector<int> distances = dijkstras_ss(G, start);
		int end;
		rep(i, 0, q)
		{
			scanf("%d", &end);
			if (end >= N || distances[end] == INT_MAX) {
				cout << "Impossible" << endline;
			}
			else {
				cout << distances[end] << endline;
			}
		}
		cout << endline;
	}
}


void KATTISshortestPathTimeTable() {
	while (true)
	{
		int N, m, q, start;
		//scanf("%d%d%d%d", &N, &m, &q, &start);
		cin >> N >> m >> q >> start;

		if (N == 0 && m == 0 && q == 0 && start == 0) //more checks??
			break;

		graph G(N);
		int to, from, w, t, P;
		rep(i, 0, m)
		{
			scanf("%d%d%d%d%d", &from, &to, &t, &P, &w);
			G.addEdge(from, to, w, t, P);
		}

		vector<int> distances = dijkstras_ss_tt(G, start);
		int end;
		rep(i, 0, q)
		{
			scanf("%d", &end);
			if (end >= N || distances[end] == INT_MAX) {
				cout << "Impossible" << endline;
			}
			else {
				cout << distances[end] << endline;
			}
		}
		cout << endline;
	}
}

void KATTISFloydWarshall()
{
	int n, m, q;
	while (true)
	{
		cin >> n >> m >> q;
		if (n == 0 && m == 0 && q == 0)
			break;

		graph G(n);
		int u, v, w;
		rep(i, 0, m)
		{
			cin >> u >> v >> w;
			G.addEdge(u, v, w);
		}

		t_FW fw = FloydWarshall(G);
		t_distancematrix& dist = fw.first;
		t_nextmatrix& next = fw.second;
		rep(i, 0, q)
		{
			cin >> u >> v;
			int d = pathlength(fw, u, v);
			if (d == FW_NEGINF)
			{
				cout << "-Infinity" << endline;
			}
			else if (d == FW_INF)
			{
				cout << "Impossible" << endline;
			}
			else
			{
				cout << d << endline;
			}
		}
		cout << endl;
	} // next test case

	int stop = 1;
}



void KATTIS_MST()
{
	int n, m;
	
	while (true)
	{
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;

		graph G(n);

		int from, to, w;
		rep(i, 0, m)
		{
			cin >> from >> to >> w;
			G.addEdge(from, to, w);
			G.addEdge(to, from, w);
		}

		vector<edge> mst = MinimumSpanningTree(G);
		// lexicographic sorting
		sort(mst.begin(), mst.end(), [](edge a, edge b) {
			// int aMin, bMin, aMax, bMax;
			// if (a.from < a.to)
			if (a.from == b.from) 
				return a.to < b.to;
			return a.from < b.from; 
		});

		int cost = 0;
		trav(e, mst)
		{
			cost += (*e).w;
		}

		if (mst.size() > 0)
		{
			cout << cost << endline;
			trav(e, mst)
			{
				cout << (*e).from << " " << (*e).to << endline;
			}
		}
		else
		{
			cout << "Impossible" << endline;
		}

	}

	int breakpoint = 1;
}

void KATTIS_MaxFlow() {

	// Read Input:
	int NUM_VERTICES, NUM_EDGES, S, T;
	cin >> NUM_VERTICES >> NUM_EDGES >> S >> T;
	FlowGraph G(NUM_VERTICES, S, T);
	G.CAPACITY_THRES = INT_MAX;

	int from, to, capacity;
	int maxcapacity = -1;
	rep(i, 0, NUM_EDGES)
	{
		cin >> from >> to >> capacity;
		maxcapacity = max(maxcapacity, capacity);
		G.AddEdge(from, to, capacity);
	}

	//threshold is set to some 2^k close to maxcapacity
	if (maxcapacity > 0)
		G.CAPACITY_THRES = (int)pow(2, floor(log(maxcapacity) / log(2.0)));

	// get max flow
	t_edgeset FF = EdmondsKarp(G);
	vector<Edge> usedEdges = FF.first;
	long long flow = FF.second;

	//output answer
	cout << G.N << " " << flow << " " << usedEdges.size() << endline;
	trav(e, usedEdges)
		cout << (*e).from << " " << (*e).to << " " << (*e).flow << endline;	
}


void KATTIS_EulerianPath() {
	int n, m;
	while (true)
	{
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;

		graph G(n);

		int from, to;
		rep(i, 0, m)
		{
			cin >> from >> to;
			G.addEdge(from, to);
		}		
		vector<int> path = eulerian_path(G);
		if (path.empty()) 
		{
			printf("Impossible\n");
		}
		else {
			for (int i = 0; i < path.size(); ++i) {
				printf("%d ", path[i]);
			}
			printf("\n");
		}
	}
}

