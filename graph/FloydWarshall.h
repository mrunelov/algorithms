#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include "common.h"
#include "graph.h"

//
// Floyd Warshall typedefs & constants
//

typedef vector<vector<int>> t_distancematrix;
typedef vector<vector<int>> t_nextmatrix;
typedef pair<t_distancematrix, t_nextmatrix> t_FW;
const int FW_INF = INT_MAX/2;
const int FW_NEGINF   = -FW_INF;
const int FW_NULLNODE = -1;

//
// Floyd Warshall Construction & Query
//

t_FW FloydWarshall(graph& G);
int pathlength(t_FW& fw, int u, int v);

#endif
