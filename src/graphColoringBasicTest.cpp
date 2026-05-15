#include <iostream>
#include <string>
#include <vector>
#include "graph.h"
#include "graphColoring.h"

void runTest(int testNum, std::string name, int expected, int actual) {
    if (expected == actual) {
        std::cout << "[PASS] Test " << testNum << ": " << name << "\n";
    } else {
        std::cout << "[FAIL] Test " << testNum << ": " << name
                  << " \n       -> Expected: " << expected << ", Got: " << actual << "\n";
    }
}

template<typename T>
void addUndirectedEdge(Graph<T>& g, T u, T v) {
    g.addEdge(u, v, 1);
    g.addEdge(v, u, 1);
}

// ==========================================
// CATEGORY 1: Trivial & Edge Cases
// ==========================================
void test01_EmptyGraph() {
    Graph<int> g;
    runTest(1, "Empty Graph (N=3)", 0, graphColoringBasic(&g, 3));
}

void test02_SingleNode() {
    Graph<int> g;
    g.addVertex(1);
    runTest(2, "Single Node (N=1)", 1, graphColoringBasic(&g, 1));
}

void test03_SingleNodeZeroColors() {
    Graph<int> g;
    g.addVertex(1);
    runTest(3, "Single Node, Zero Colors (Spill)", -1, graphColoringBasic(&g, 0));
}

void test04_DisconnectedNodes() {
    Graph<int> g;
    for(int i=1; i<=5; i++) g.addVertex(i);
    runTest(4, "5 Disconnected Nodes (N=1)", 1, graphColoringBasic(&g, 1));
}

// ==========================================
// CATEGORY 2: Trees & Bipartite
// ==========================================
void test05_PathGraph() {
    Graph<int> g;
    for(int i=1; i<=3; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3);
    runTest(5, "Path Graph of 3 nodes (N=2)", 2, graphColoringBasic(&g, 2));
}

void test06_StarGraph() {
    Graph<int> g;
    for(int i=1; i<=5; i++) g.addVertex(i);
    for(int i=2; i<=5; i++) addUndirectedEdge(g, 1, i);
    runTest(6, "Star Graph (N=2)", 2, graphColoringBasic(&g, 2));
}

void test07_BinaryTree() {
    Graph<int> g;
    for(int i=1; i<=7; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 1, 3);
    addUndirectedEdge(g, 2, 4); addUndirectedEdge(g, 2, 5);
    addUndirectedEdge(g, 3, 6); addUndirectedEdge(g, 3, 7);
    runTest(7, "Binary Tree (N=2)", 2, graphColoringBasic(&g, 2));
}

void test08_EvenCycle_Spill() {
    Graph<int> g;
    for(int i=1; i<=4; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3);
    addUndirectedEdge(g, 3, 4); addUndirectedEdge(g, 4, 1);
    runTest(8, "Even Cycle C4 (N=2, Spill)", -1, graphColoringBasic(&g, 2));
}

void test09_EvenCycle_Success() {
    Graph<int> g;
    for(int i=1; i<=4; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3);
    addUndirectedEdge(g, 3, 4); addUndirectedEdge(g, 4, 1);
    runTest(9, "Even Cycle C4 (N=3)", 2, graphColoringBasic(&g, 3));
}

// ==========================================
// CATEGORY 3: Odd Cycles
// ==========================================
void test10_Triangle_Spill() {
    Graph<int> g;
    for(int i=1; i<=3; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3); addUndirectedEdge(g, 3, 1);
    runTest(10, "Triangle K3 (N=2, Spill)", -1, graphColoringBasic(&g, 2));
}

void test11_Triangle_Success() {
    Graph<int> g;
    for(int i=1; i<=3; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3); addUndirectedEdge(g, 3, 1);
    runTest(11, "Triangle K3 (N=3)", 3, graphColoringBasic(&g, 3));
}

void test12_Pentagon() {
    Graph<int> g;
    for(int i=1; i<=5; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3);
    addUndirectedEdge(g, 3, 4); addUndirectedEdge(g, 4, 5); addUndirectedEdge(g, 5, 1);
    runTest(12, "Pentagon C5 (N=3)", 3, graphColoringBasic(&g, 3));
}

// ==========================================
// CATEGORY 4: Complete Graphs (Cliques)
// ==========================================
void test13_Tetrahedron_Spill() {
    Graph<int> g;
    for(int i=1; i<=4; i++) g.addVertex(i);
    for(int i=1; i<=4; i++) {
        for(int j=i+1; j<=4; j++) addUndirectedEdge(g, i, j);
    }
    runTest(13, "Tetrahedron K4 (N=3, Spill)", -1, graphColoringBasic(&g, 3));
}

void test14_Tetrahedron_Success() {
    Graph<int> g;
    for(int i=1; i<=4; i++) g.addVertex(i);
    for(int i=1; i<=4; i++) {
        for(int j=i+1; j<=4; j++) addUndirectedEdge(g, i, j);
    }
    runTest(14, "Tetrahedron K4 (N=4)", 4, graphColoringBasic(&g, 4));
}

void test15_Pentacle() {
    Graph<int> g;
    for(int i=1; i<=5; i++) g.addVertex(i);
    for(int i=1; i<=5; i++) {
        for(int j=i+1; j<=5; j++) addUndirectedEdge(g, i, j);
    }
    runTest(15, "Complete Graph K5 (N=5)", 5, graphColoringBasic(&g, 5));
}

// ==========================================
// CATEGORY 5: Complex Topologies
// ==========================================
void test16_FanGraph() {
    Graph<int> g;
    for(int i=1; i<=6; i++) g.addVertex(i);
    for(int i=1; i<=4; i++) addUndirectedEdge(g, i, i+1);
    for(int i=1; i<=5; i++) addUndirectedEdge(g, 6, i);
    runTest(16, "Fan Graph F5 (N=3)", 3, graphColoringBasic(&g, 3));
}

void test17_WheelGraph_Spill() {
    Graph<int> g;
    for(int i=1; i<=5; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3);
    addUndirectedEdge(g, 3, 4); addUndirectedEdge(g, 4, 1);
    for(int i=1; i<=4; i++) addUndirectedEdge(g, 5, i);
    runTest(17, "Wheel Graph W4 (N=3, Spill)", -1, graphColoringBasic(&g, 3));
}

void test18_WheelGraph_Success() {
    Graph<int> g;
    for(int i=1; i<=5; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3);
    addUndirectedEdge(g, 3, 4); addUndirectedEdge(g, 4, 1);
    for(int i=1; i<=4; i++) addUndirectedEdge(g, 5, i);
    runTest(18, "Wheel Graph W4 (N=4)", 3, graphColoringBasic(&g, 4));
}

// ==========================================
// CATEGORY 6: Mixed & Stress Tests
// ==========================================
void test19_DisconnectedMixed() {
    Graph<int> g;
    for(int i=1; i<=7; i++) g.addVertex(i);
    addUndirectedEdge(g, 1, 2); addUndirectedEdge(g, 2, 3); addUndirectedEdge(g, 3, 1);
    addUndirectedEdge(g, 4, 5); addUndirectedEdge(g, 4, 6); addUndirectedEdge(g, 4, 7);
    runTest(19, "Disconnected K3 and Star (N=3)", 3, graphColoringBasic(&g, 3));
}

void test20_BipartiteHeuristicLimitation() {
    Graph<int> g;
    for(int i=1; i<=6; i++) g.addVertex(i);
    int left[] = {1, 2, 3};
    int right[] = {4, 5, 6};
    for(int l : left) {
        for(int r : right) {
            addUndirectedEdge(g, l, r);
        }
    }
    runTest(20, "K3,3 Heuristic Limitation (N=2, Spill)", -1, graphColoringBasic(&g, 2));
}

// ==========================================
// MAIN RUNNER
// ==========================================
int main() {
    std::cout << "--- Starting Greedy Graph Coloring Test Suite ---\n\n";

    test01_EmptyGraph();
    test02_SingleNode();
    test03_SingleNodeZeroColors();
    test04_DisconnectedNodes();
    std::cout << "\n";

    test05_PathGraph();
    test06_StarGraph();
    test07_BinaryTree();
    test08_EvenCycle_Spill();
    test09_EvenCycle_Success();
    std::cout << "\n";

    test10_Triangle_Spill();
    test11_Triangle_Success();
    test12_Pentagon();
    std::cout << "\n";

    test13_Tetrahedron_Spill();
    test14_Tetrahedron_Success();
    test15_Pentacle();
    std::cout << "\n";

    test16_FanGraph();
    test17_WheelGraph_Spill();
    test18_WheelGraph_Success();
    std::cout << "\n";

    test19_DisconnectedMixed();
    test20_BipartiteHeuristicLimitation();

    std::cout << "\n--- Test Suite Complete ---\n";
    return 0;
}