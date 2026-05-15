#ifndef DA_PROJECT_2_DATASTRUCTS_H
#define DA_PROJECT_2_DATASTRUCTS_H

#include <string>
#include "map"
#include "unordered_map"
#include <vector>
#include "graph.h"
#include <set>

using namespace std;
/**
 * @brief Types of register allocation algorithms.
 *
 * - basic:     Greedy graph coloring without modifications to the graph.
 * - splitting: Iterative web splitting to reduce interference.
 * - spilling:  Web spilling (removal) when registers aren't enough.
 * - free:     Variant free for experimentation.
 *
 * These values correspond directly to the "algorithm:" field in the
 * second input file().
 */
enum alg_type {
    basic,
    splitting,
    spilling,
    free_
};
/**
 * @brief Stores the algorithm configuration parsed from the second input file.
 *
 * The parser fills:
 * - type: which algorithm variant to use,
 * - val:  an integer parameter (max splits or max spills).
 *
 * For "basic" and "free", val = 0.
 * For "splitting" and "spilling", val is read from the input file.
 */
struct algorithm { //struct for parser to store information about the second input file
    alg_type type;
    int val;
};
/**
 * @brief Represents a single live web of a variable.
 *
 * A web is the combination of one or more live ranges belonging to the same
 * variable. The parser initially creates one web per live-range line in the
 * input file. After parsing, mergeWebs() merges all overlapping live ranges
 * of the same variable into a single web.
 *
 * Fields:
 * - var_name: name of the variable.
 * - start:    program lines where the web begins (lines ending with '+').
 * - end:      program lines where the web ends (lines ending with '-').
 * - lines:    all program points where the variable is live.
 *
 * All vectors are sorted after merging, and the interfere() function assumes
 * this ordering.
 */
struct web { //struct for storing information about each web
    string var_name;
    vector<int> start;
    vector<int> end;
    vector<int> lines;
    string id;

    bool operator==(const web& other) const {
        return (var_name == other.var_name && lines == other.lines);
    }
    
};

/**
 * @brief Global parameters produced by the parser.
 *
 * This structure contains all information extracted from the two input files:
 *
 * - webs: list of all merged webs.
 * - alg:  algorithm type and parameter.
 * - regs: number of available registers.
 * - valid: set to false if any parsing error occurs.
 */
struct params { //has all information from the input files after being parsed
    vector<web> webs;
    algorithm alg;
    int regs;

    bool valid;
};
/**
 * @brief Represents a set of webs that do not interfere with each other.
 *
 * Used in the final output to group webs that share the same register.
 * Each assignment corresponds to one register.
 */
struct assignment { //webs that dont interfere with eachother
    vector<web> webs;
};
/**
 * @brief Final result of the register allocation algorithm.
 *
 * Contains:
 * - webs:        the final list of webs (possibly modified by splitting).
 * - assignments: groups of webs that share the same register.
 * - regs:        number of registers actually used.
 * - possible:    false if allocation failed (all webs must be spilled).
 */
struct result { //final result of the algorithm
    vector<web> webs;
    vector<assignment> assignments;
    vector<web> spilledWebs;
    int regs;
    bool possible;
};

struct order { //struct for storing the order of webs
    int index;
    web w;
};
<<<<<<< HEAD



=======
/**
 * @brief Determines whether two webs interfere.
 *
 * Two webs interfere if their live ranges overlap at any program point.
 * The function assumes that lines, start, and end vectors are sorted.
 *
 * If the only shared line is one where:
 *   - web A ends (due to a read), and
 *   - web B begins (due to a write),
 * then the webs do not interfere.
 *
 * @return True if the webs interfere, false otherwise.
 */
>>>>>>> main
bool interfere(web a, web b);

#endif