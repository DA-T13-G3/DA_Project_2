#ifndef DA_PROJECT_2_CREATEGRAPH_H
#define DA_PROJECT_2_CREATEGRAPH_H
#include "dataStructs.h"
#include <algorithm>
/**
 * @brief Builds the graph from the set of webs.
 *
 * This function constructs a graph where each web corresponds to a vertex.
 * For every pair of webs, an interference edge is added if their live ranges
 * overlap according to 'interfere()'. The resulting graph is the
 * input for the register allocation algorithms.
 * Time complexity: O(N^2 * L)
 *
 * @param info  Global parameters containing the list of webs to insert in the graph.
 *
 * @return A Graph<web> object representing the full interference graph.
 */
Graph<web>create(params info);
#endif