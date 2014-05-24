//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#ifndef FLOWGRAPH_H
#define FLOWGRAPH_H

#include "common.h"


struct Edge
{
	int from, to, reverse;
	bool isReverse;
	int capacity, restCapacity, flow;

	Edge(int from, int to, int capacity, bool isReverse = false)
		: from(from), to(to), capacity(capacity),
		restCapacity(capacity), flow(0), reverse(-1), isReverse(isReverse)
	{}

	Edge()
		: from(-1), to(-1), capacity(0),
		restCapacity(0), flow(0), reverse(-1), isReverse(false)
	{}
	
};

struct Node
{
	int idx;
	vector<int> adj;
	int currentflow;
	int prev, edgeIn; //backtrack pointers

	Node() : idx(-1), prev(-1), currentflow(INT_MAX), edgeIn(-1) {}
	void AddEdge(int edge) { adj.push_back(edge); }
};


class FlowGraph
{
public:
	int N; 	// |V| = N
	int M;  // |E| = M
	vector<Node> V;
	vector<Edge> E;


	int S, T; //source & sink 
	int CAPACITY_THRES;
	int edgeIn;

	FlowGraph();
	FlowGraph(int N, int S, int T);

	void AddEdge(int from, int to, int capacity);
	Node& GetSource();
	Node& GetSink();

	void SetFlow(int node, int flow);


	~FlowGraph();
};

#endif