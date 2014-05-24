//
// @authors:
// Martin Runelöv
// Philip Sköld
//

//
// Graph class (currently used for Dijkstras, Eulerian Path and MST)
//

#ifndef GRAPH_H
#define GRAPH_H

#include "common.h"

//forward declarations
struct node;
struct edge;
class graph;

// EDGE

struct edge
{
	int from;
	int to;
	int w;
	int t; // timetable search
	int P; // timetable search
	bool visited; // eulerian path
	int idx; // index in E
	edge(int from, int to, int w=-1) : from(from), to(to), w(w) {
		visited = false;
	};
	edge(int from, int to, int w, int t, int P) : from(from), to(to), w(w), t(t), P(P) {};
};

// NODE

struct node
{
	vector<edge> adj;
	void add(edge e);
	int inDeg; // eulerian path
	int outDeg;
	node() {
		inDeg = 0;
		outDeg = 0;
	}
};

// GRAPH
 
class graph
{
public:
	vector<node> V;
	vector<edge> E;

	int N; // |V|

	graph();
	graph(int N);
	
	vector<edge>& getAdj(int node); // get all adjacent vertices of a node
	node& getNode(int idx);

	/**
	 * Reconstructs paths from a parent vector
	 */
	vector<int> getPath(vector<int>& parent, int start, int end); 

	/**
	 * Calculates path length of a given path using the edge weights in the nodes
	 */
	int getPathLength(const vector<int>& path);
	int getWeight(int from, int to);

	void addEdge(int from, int to);
	void addEdge(int from, int to, int w);
	void addEdge(int from, int to, int w, int t, int P);

	~graph();
};

#endif