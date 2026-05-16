#ifndef DA_PROJECT_2_SPILLING_H
#define DA_PROJECT_2_SPILLING_H

#include "dataStructs.h"
#include "graphColoring.h"
#include "createGraph.h"
#include "buildResult.h"
#include <algorithm>
#include <limits>
#include <functional>


struct result spill(Graph<web>* g, params info, function<int(Graph<web>* g, int)> coloring);

#endif
