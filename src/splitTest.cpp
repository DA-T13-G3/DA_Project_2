//
// Created by gustavobastos on 15/05/26.
//
#include "parser.h"
#include "createGraph.h"
#include "graphColoring.h"
#include "buildResult.h"
#include "spilling.h"
#include "writeAssignments.h"
#include "splitting.h"
/*
g++  splitTest.cpp parser.cpp  createGraph.cpp  dataStructs.cpp  buildResult.cpp  splitting.cpp  writeAssignments.cpp -o splitTest
./splitTest
 */
int main() {
    params info = parse("../input/ranges/splitRange.txt", "../input/registers/registersSplit.txt");
    Graph<web> graph = create(info);
    Graph<web>* g = &graph;
    struct result res;
    if (info.alg.type == splitting_ ){
        splitting(g, info);
        res=build(g, info);
    }

    write(res);

    return 0;

}