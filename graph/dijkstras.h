//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H

#include "common.h"
#include "graph.h"

/**
 * Comparator struct for nodes in dijstras.
 * Compares by distance in a distance vector 'dist', smallest to largest.
 * If equal distance, node indices are compared, largest to smallest.
 */
struct Cmp;

/**
 * dijkstras single source shortest path
 * @return: vector of parent nodes in shortest paths from nodes to the source 'start'
 * (If multiple shortest paths exist, an arbitrary one is chosen)
 */
vector<int> dijkstras_ss(graph& G, int start);


/**
 * dijkstras single source shortest path with time table constraints of the form (t + P),
 * which states that we can only use an edge from time t, and every P'th time step after time t.
 * Example: t = 15, P = 10. We can visit this edge at times 15,25,35,45 etc.
 * @return: vector of shortest distances from the source 'start' for each node.
 * OBS: (The function also has the option of returning a parent vector, like the original dijkstras above, 
 * but in order to calculate path lengths from this the distance vector is also needed.)
 */
vector<int> dijkstras_ss_tt(graph& G, int start);

/**
 * Help function for dijkstras_ss_tt_distances.
 * Returns the time we have to wait before we can use the edge e.
 * Returns -1 if we can't visit the edge (if P == 0 and t > e.t)
 */
int reachableAt(edge e, int t);


#endif // end header guard