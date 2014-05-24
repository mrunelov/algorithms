//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#ifndef EDMONDKARP_H
#define EDMONDKARP_H

#include "common.h"
#include "FlowGraph.h"

static int BFS_ID = 1; // used instead of boolean visited arrays in each BFS
typedef pair<vector<Edge>, long long> t_edgeset; // return type for EdmondKarp

/*
 * The Edmonds-Karp algorithm to find the maximum flow in a flow network
 * @return: The edges with positive flow and the total maximum flow of the flow network G
 */
t_edgeset EdmondsKarp(FlowGraph& G); 

/*
 * Help function for Edmonds-Karp
 * Calculates residual capacity using BFS
 */
int getResidual(FlowGraph& G); 

#endif
