#include "src/parser.h"
#include "src/createGraph.h"
#include "src/graphColoring.h"
#include <iostream>

int main() {
    params info = parse("input/ranges/splitRange.txt", "input/registers/registersSplit.txt");
    Graph<web> g = create(info);
    for (auto v : g.getVertexSet()) {
        if (v->getInfo().id == "0") v->setVisited(true);
    }
    int res = graphColoringBasic(&g, info.regs);
    std::cout << "RES WITH SPILL: " << res << std::endl;
    return 0;
}
