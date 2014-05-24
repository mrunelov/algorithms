#include "FlowGraph.h"


//
// Residual Graph
//


FlowGraph::FlowGraph()
{
}

FlowGraph::FlowGraph(int N, int S, int T)
	: N(N), S(S), T(T)
{
	V.resize(N);
	rep(i, 0, N)
		V[i].idx = i; //label vertices
}

void FlowGraph::AddEdge(int from, int to, int capacity)
{
	// new edges with id forw and backw
	Edge forward(from, to, capacity);
	Edge backward(to, from, 0, true); //reverse edge
	int forw = E.size();
	int backw = E.size() + 1;
	
	M += 2; // two more edges added

	//reverse pointers
	forward.reverse = backw;
	backward.reverse = forw;

	//add to E and V
	E.push_back(forward);
	E.push_back(backward);
	V[from].AddEdge(forw);
	V[to].AddEdge(backw);

}

Node& FlowGraph::GetSource()
{
	return V[S];
}

Node& FlowGraph::GetSink()
{
	return V[T];
}

void FlowGraph::SetFlow(int node, int flow)
{
	V[node].currentflow = flow;
}

FlowGraph::~FlowGraph()
{
}
