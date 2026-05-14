#include "parser.h"
#include "createGraph.h"
#include "graphColoring.h"
#include "buildResult.h"
#include "spilling.h"
#include "writeAssignments.h"

int main() {
    params info = parse("../input/ranges/rangesCustom.txt", "../input/registers/registersCustom.txt");
    Graph<web> graph = create(info);
    Graph<web>* g = &graph;
    struct result res;
    if (info.alg.type == spilling){
        res = spill(g, info);
    }

    write(res);
    
    return 0;

}