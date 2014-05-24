// authors:
//  @Philip Sköld
//  @Martin Runelöv

#ifndef MST_H
#define MST_h

#include "graph.h"

/**
 * Constructs a Minimum Spanning Tree (MST) of G.
 * @return: A minimum spanning tree of G.
 * If multiple MST's exist, an arbitrary one is returned.
 * If forests exist, an empty vector is returned.
 */
vector<edge> MinimumSpanningTree(graph G);

#endif // header guard