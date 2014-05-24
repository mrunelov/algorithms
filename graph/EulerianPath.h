#ifndef EULERIANPATH_H
#define EULERIANPATH_H

#include "common.h"
#include "graph.h"

/**
 * Help function for eulerian_path
 * Checks if node degrees are valid and sets a dummy edge
 * to create an eulerian cycle if needed
 */
pair<int,int> set_dummy(graph& G);

/**
 * Finds an eulerian path in G
 * @return: The nodes visited in an eulerian path
 * or an empty vector if none exists
 */
vector<int> eulerian_path(graph& G);
void eulerian_path(graph& G, int u);


#endif // end header guard
