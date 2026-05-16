#include "parser.h"
#include "createGraph.h"
#include "graphColoring.h"
#include "buildResult.h"
#include "spilling.h"
#include "writeAssignments.h"

/*
g++  spillTest.cpp parser.cpp  createGraph.cpp  dataStructs.cpp  buildResult.cpp  spilling.cpp  writeAssignments.cpp -o spillTest
./spillTest
 */
int main() {
    params info = parse("../input/ranges/rangesCustom.txt", "../input/registers/registersCustom.txt");
    Graph<web> graph = create(info);
    Graph<web>* g = &graph;
    struct result res;
    if (info.alg.type == spilling){
        res = spill(g, info, graphColoringFree<web>);
    }

    write(res);
    
    return 0;

}