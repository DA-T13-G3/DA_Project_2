//
// Created by gustavobastos on 16/05/26.
//

#include "allocationTool.h"

/**
 * @brief Executes the register allocation tool using input and output file paths.
 * * This function parses the provided live range and register configuration files
 * to populate the internal parameter structure. If the parsing is successful, it
 * delegates the graph creation and coloring process to the overloaded
 * allocationTool function.
 * * @param rangeInputFile The file path containing the live ranges (webs) of variables.
 * @param registerInputFile The file path containing register configuration and the chosen algorithm.
 * @param outputFile The file path where the final allocation results will be written.
 * @return int Returns 0 upon successful allocation and file writing, or -1 if parsing fails.
 */
int allocationTool(const string& rangeInputFile,const string&registerInputFile, const string& outputFile) {
    params info = parse(rangeInputFile, registerInputFile);
    if (!info.valid) {
        printf("Parsing errors occurred (file not found or does not have the desired format) \n");
        return -1;
    }
    return allocationTool(info,outputFile);
}
/**
 * @brief Core execution engine for the register allocation tool.
 * * This function takes pre-parsed parameters, builds the interference graph,
 * and executes the designated register allocation algorithm based on the configuration
 * (Basic, Spilling, Splitting, or Free). Once the graph is colored, it builds the
 * final result structure and writes it to the specified output file.
 * * @param info A reference to the parsed parameters structure containing webs, register limits, and the selected algorithm.
 * @param outputFile The file path where the final allocation results will be written.
 * @return int Returns 0 upon successful execution and file writing, or -1 if the parameters are invalid or the algorithm type is unrecognized.
 */
int allocationTool(  params& info, const string& outputFile) {
    if (!info.valid) {
        printf("Parsing errors occurred (file not found or does not have the desired format) \n");
        return -1;
    }
    Graph<web> graph = create(info);
    Graph<web>* g = &graph;
    struct result res;

    switch (info.alg.type) {
        case basic:
            graphColoringBasic(g,info.regs);
            res=build(g,info);
            break;
        case spilling:
            graphColoringBasicWithSpilling(g,info.regs);
            res=build(g,info);
            break;
        case splitting_:
            splitting(g, info);
            res=build(g, info);
            break;
        case free_:
            res = spill(g, info, graphColoringFree<web>);
            break;
        default:
            printf("allocationTool: failed to identify the algorithm type\n");
            return -1;
    }

    write(res,outputFile);
    return 0;

}
