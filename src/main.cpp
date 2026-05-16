//
// Created by gustavobastos on 16/05/26.
//
#include "allocationTool.h"
/*
g++  main.cpp allocationTool.cpp parser.cpp  createGraph.cpp  dataStructs.cpp  buildResult.cpp  spilling.cpp splitting.cpp  writeAssignments.cpp -o Tool
./Tool
*/
int main(int argc, char*argv[]) {
    if (argc ==5 && strcmp(argv[1],"-b")==0) {
        //
        // ex:
        // ./Tool -b "../input/ranges/basicRange.txt" "../input/registers/registersBasic.txt" "../output/output.txt"

        allocationTool(argv[2],argv[3],argv[4]);
    }
    else if (argc ==1) {
        //Menu
    }
    else {

        printf("2 Usages \n");
        printf("Usage: ./Tool -b [rangeInputFile] [registerInputFile] [outputFile] \n");
        printf("Usage: ./Tool  \n");

    }
}