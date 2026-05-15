#include "src/parser.h"
#include "src/createGraph.h"
#include "src/graphColoring.h"
#include <iostream>

int main() {
    params info = parse("input/ranges/splitRange.txt", "input/registers/registersSplit.txt");
    Graph<web> g = create(info);
    int res = graphColoringBasic(&g, info.regs);
    std::cout << "RES: " << res << std::endl;
    return 0;
}
