#ifndef DA_PROJECT_2_BUILDRESULT_H
#define DA_PROJECT_2_BUILDRESULT_H

#include "dataStructs.h"

/**
 * @brief Translates the colored interference graph into the final register allocation result to be written to a file.
 * 
 * This function processes the allocated graph state after a coloring attempt. It iterates 
 * through all vertices to separate successfully allocated variables from spilled ones (which 
 * are flagged as 'visited'). It groups successfully colored variables into distinct color buckets, 
 * maps those buckets directly to physical register assignments, and determines if the final 
 * allocation successfully respected the architecture's register limit.
 * 
 * @param g Constant pointer to the interference graph containing coloring and spill state.
 * @param info Constant reference to the master configuration structure holding architectural information.
 * @return A populated 'result' structure detailing the register assignments, spilled variables, 
 * total physical registers utilized, and a boolean flag indicating if allocation succeeded.
 */
struct result build(Graph<web>* g, const params& info);
struct result build(Graph<web>* g,const params& info);

#endif
