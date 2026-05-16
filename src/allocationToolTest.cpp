//
// Created by gustavobastos on 16/05/26.
//
#include "allocationTool.h"
/*
g++  allocationToolTest.cpp allocationTool.cpp parser.cpp  createGraph.cpp  dataStructs.cpp  buildResult.cpp  spilling.cpp splitting.cpp  writeAssignments.cpp -o allocationToolTest
./allocationToolTest
*/
int main() {
    allocationTool( "../input/ranges/basicRange.txt", "../input/registers/registersBasic.txt","../output/output.txt");
    return 0;
}