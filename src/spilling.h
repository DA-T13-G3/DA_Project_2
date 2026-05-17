#ifndef DA_PROJECT_2_SPILLING_H
#define DA_PROJECT_2_SPILLING_H

#include "dataStructs.h"
#include "graphColoring.h"
#include "createGraph.h"
#include "buildResult.h"
#include <algorithm>
#include <limits>
#include <functional>
#include <cmath>

/**
 * @brief Builds a result struct while spilling a certain amount of webs into memory.
 * 
 * This method extracts the graph's vertices, isolates a strategic subset of size 'X' containing 
 * the highest-degree candidates, and runs a binary search over the range 
 * of possible spill numbers. The search uses 'attempt()' to find the smallest number of spills needed.
 * Finally, it invokes 'finalSpill()' to commit the highest-efficiency combination and calls 
 * 'build()' to construct the final allocation report.
 * 
 * @details Details on the Heuristics Applied
 * To make this function run in a practical timeframe, it tries to spill a maximum of log2(total webs),
 * which significantly decreases its time complexity. It starts by trying
 * to spill the nodes with the biggest degrees, as these are the ones most likely to increase the
 * number of necessary registers, and then moves on to spilling nodes with lower degrees if that
 * doesn't work.
 * This compromise trades unnecessary precision for a very significant increase in speed, which is why
 * it was chosen.
 * 
 * **Time Complexity:**
 * O(W * log(W) + (2^log(W) / sqrt(log(W))) * (W + I)) where 'W' is the number of webs and 'I' is the total amount of interferences between webs.
 * 
 * @param g Pointer to the interference graph to process.
 * @param info Struct holding algorithm settings, limits, and user choices.
 * @param coloring Function that will execute the coloring of the graph.
 * @return A result structure stating whether allocation succeeded and mapping variables to registers.
 */
struct result spill(Graph<web>* g, params info, function<int(Graph<web>* g, int)> coloring);

#endif
