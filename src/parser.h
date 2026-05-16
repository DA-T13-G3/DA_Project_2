#ifndef DA_PROJECT_2_PARSER_H
#define DA_PROJECT_2_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <unistd.h>
#include <set>
#include "dataStructs.h"

/**
 * @brief Parses the input file containing the live ranges for the variables.
 * 
 * This function reads the file specified by `path1`, filters out comments 
 * and empty lines, and extracts live range information for each variable into a params1 structure.
 * It identifies definition points (marked with '+') and end-of-life points (marked with '-').
 * If file opening fails or string-to-integer conversion errors occur, the validation flag 
 * within the parameters structure is set to false.
 * 
 * @param path1 Relative path to the live ranges text file.
 * @param params Reference to the params1 output structure where extracted webs and validity state are stored.
 */
void parse1(string path1, params1 &params);

/**
 * @brief Parses the input file containing the register number and algorithm type and value.
 * 
 * This function reads the file specified by `path2`, filters out comments 
 * and empty lines, and extracts information regarding the number of available registers and
 * the type of algorithm to be used while coloring the resulting graph, as well as its
 * value into a params2 structure.
 * If file opening fails or string-to-integer conversion errors occur, and if no valid
 * algorithm type and respective value are detected, the validation flag within the
 * parameters structure is set to false.
 * 
 * @param path2 Relative path to the allocator configuration file.
 * @param params Reference to the params2 output structure where extracted data and validity state are stored.
 */
void parse2(string path2, params2 &params);

/**
 * @brief Creates a params structure with all the data extracted from two input files.
 * 
 * This function organizes the live ranges of each variable into webs, gives them an id and then
 * merges both params1 and params2 into a single unified params structure with all the data from them.
 * If even a single one of the two params this function receives has its validity set to false, the validity
 * of the resulting params structure will also be false.
 * 
 * @param params1 Reference to the params1 output structure where extracted webs and their
 * validity state are stored.
 * @param params2 Reference to the params2 output structure where extracted data and their
 * validity state are stored.
 * @return The structure containing all information necessary for the main algorithm.
 */
params parse(params1 &params1, params2 &params2);

/**
 * @brief Creates a params structure with all the data extracted from two input files.
 * 
 * This function calls upon parse1 and parse2 to parse their respective types of files and then 
 * organizes the live ranges of each variable into webs, gives them an id and then
 * merges the params1 and params2 resulting from the earlier function calls into a single
 * unified params structure with all the data from them.
 * If even a single one of the two params this function receives has its validity set to false, the validity
 * of the resulting params structure will also be false.
 * 
 * @param path1 Relative path to the live ranges text file.
 * @param path2 Relative path to the allocator configuration text file.
 * @return The structure containing all information necessary for the main algorithm.
 */
params parse (const string& path1, const string& path2);

#endif