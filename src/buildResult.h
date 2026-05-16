#ifndef DA_PROJECT_2_BUILDRESULT_H
#define DA_PROJECT_2_BUILDRESULT_H

#include "dataStructs.h"

//builds the result struct to be written to the output file, based on the graph and the input parameters (currently only works for the spilling algorithm, but can be adapted for the others if needed)
struct result build(Graph<web>* g,const params& info);

#endif
