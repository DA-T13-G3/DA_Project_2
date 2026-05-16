//
// Created by gustavobastos on 16/05/26.
//

#ifndef DA_PROJECT_2_ALLOCATION_TOOL_H
#define DA_PROJECT_2_ALLOCATION_TOOL_H

#include "parser.h"
#include "createGraph.h"
#include "graphColoring.h"
#include "buildResult.h"
#include "spilling.h"
#include "writeAssignments.h"
#include "splitting.h"

#include "menu.h"


int allocationTool(const string& rangeInputFile,const string&registerInputFile, const string& outputFile);
int allocationTool( params& info, const string& outputFile);


#endif //DA_PROJECT_2_ALLOCATION_TOOL_H