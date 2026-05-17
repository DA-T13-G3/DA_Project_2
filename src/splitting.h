#ifndef DA_PROJECT_2_SPLITTING_H
#define DA_PROJECT_2_SPLITTING_H
#include <algorithm>
#include "dataStructs.h"
#include "graphColoring.h"
/**
 * @brief Splits a web into two smaller webs.
 *
 * This function selects a web in the graph (the one with
 * the highest degree) and divides it into two new webs. The original web is
 * removed from the graph, and the two derived webs are inserted with updated 
 * edges. The vector webs in params is also updated.
 *
 * @param g     Pointer to the graph of webs.
 * @param info  Global parameters, including the list of webs and algorithm settings.
 */
void split(Graph<web> *g, params&info);
/**
 * @brief Attempts to color the graph using iterative web splitting.
 *
 * This function repeatedly tries to color the graph using the basic greedy
 * coloring algorithm. If coloring fails and the maximum number of allowed
 * splits has not been reached, one web is split (via split()) and the graph is
 * recolored. The process continues until either:
 *   - the graph becomes colorable with the available registers, or
 *   - the maximum number of splits is reached.
 * Time Complexity: Θ(k · (E + V · L))
 * 
 *   k - Actual number of splits performed before coloring succeeds (k ≤ S)
 *   E - Number of interference edges in the graph
 *   V - Number of webs (vertices)
 *   L - Average number of lines in a live range

 
 *
 * @param g     Pointer to the graph of webs.
 * @param info  Global parameters, including register count and algorithm settings.
 *
 * @return The number of colors used if successful, or -1 if allocation is impossible.
 */
int splitting(Graph<web> *g, params&info);

#endif