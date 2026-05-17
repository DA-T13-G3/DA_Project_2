#ifndef DA_PROJECT_2_WRITEASSIGNMENTS_H
#define DA_PROJECT_2_WRITEASSIGNMENTS_H

#include "dataStructs.h"
#include <vector>
#include <fstream>
#include <set>

using namespace std;

/**
 * @brief Exports the finalized register allocation results to an output file.
 * 
 * This function writes the contents of an allocation 'result' structure into a clean, 
 * human-readable text format. It logs the consolidated metrics of all webs, 
 * reconstructs their exact lifetime intervals with specific boundary 
 * markers, and maps them to their allocated hardware registers or memory slots.
 * 
 * @details **Output format for the spilling and plitting algorithms:**
 * **Spilling:** The webs spilled by the spilling algorithm will be commited into memory
 * and this allocation will be represented by 'M(spilled): web{id}'.
 * **Splitting:** The webs that were split will have their id altered. Ex.: web0 becomes web0.0 and web0.1.
 * 
 * @param res The constant reference to the global allocation report payload.
 * @param outputFile The file path string indicating where the compilation report should be saved.
 */
void write(const result &res,const string& outputFile="../output/output.txt");

#endif

