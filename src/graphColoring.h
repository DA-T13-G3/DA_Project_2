//
// Created by gustavobastos on 27/04/26.
//

#ifndef PROJETO2_GRAPHCOLORING_H
#define PROJETO2_GRAPHCOLORING_H

#include "graph.h"
#include "unordered_map"

int graphColoringTestSuite();


int graphColoringBasicTestSuite();

/**
 * @brief Recursive auxiliary function for Depth-First Search (DFS) graph coloring.
 * The time complexity is O(|V|^2) and the space complexity is O(V).
 *
 * @details This function acts as the recursive engine for the DFS coloring algorithm.
 * For a given vertex, it examines all adjacent vertices to determine which colors
 * are already taken. It assigns the lowest available color index (0-indexed) to
 * the current vertex and updates the highest color index used so far. Finally,
 * it recursively calls itself on all unvisited adjacent vertices to continue the
 * DFS traversal.
 *
 * @tparam T The data type stored within the vertex (e.g., int, std::string).
 *
 * @param v Pointer to the current vertex being visited and colored.
 * @param biggestColor Reference to an integer tracking the highest color index
 *                     assigned across the entire graph. If the current vertex gets
 *                     a color higher than this value, it updates this reference.
 * @param usedColors Reference to a boolean vector used to quickly
 *                   flag which colors are currently taken by the neighbors of 'v'.
 *                   It is dynamic and allocate new colors when necessary.
 *                   (Note: The function should reset the modified indices back
 *                   to 'false' before assigning the vertex color, to get the
 *                   vector clean after the past recursive calls).
 */
template<typename T>
void graphColoringFree(Vertex<T>* v,int& biggestColor,std::vector<bool>&usedColors) {
    v->setVisited(true);
    for (int i=0;i<biggestColor;i++) {
        usedColors[i] = false;
    }
    for (auto &e:v->getAdj()) {
        Vertex<T>*w=e->getDest();
        if (w->getNum()!=-1) {
            usedColors[w->getNum()]=true;
        }

    }
    int i=0;
    bool found_color=false;
    for (const auto &c:usedColors) {
        if (!c) {
            v->setNum(i);
            found_color=true;
            break;
        }
        i++;
    }
    if (!found_color) {
        biggestColor=i+1;
        v->setNum(i);
        usedColors.push_back(false);
    }

    biggestColor=std::max(biggestColor,i+1);

    for (auto &e:v->getAdj()) {
        Vertex<T>*w=e->getDest();
        if (!w->isVisited()) {
            w->setVisited(true);
            graphColoringFree(w,biggestColor,usedColors);
        }
    }
}


/**
 * @brief Colors a graph using a Depth-First Search (DFS) traversal and a greedy algorithm.
 * The time complexity is O(|V|^2) and the space complexity is O(V)
 *
 * @details This function traverses the given graph using Depth-First Search (DFS).
 * As it visits each vertex, it assigns the vertex the lowest possible color index
 * (starting from 0) that is not currently used by any of its adjacent vertices.
 *
 * Note: While this approach is fast and often uses a small number of colors,
 * it is a greedy heuristic. The DFS traversal order can sometimes lead to
 * suboptimal colorings (e.g., using 4 colors on a graph that only requires 3,
 * such as the Fan Graph F5).
 *
 * @tparam T The data type stored within the vertex (e.g., int, std::string).
 *
 * @param g A pointer to the Graph object to be colored. The graph must have
 *          bidirectional (undirected) edges for adjacent colors to be checked correctly. The graphs node
 *
 * @return Returns the total number of colors used to color the graph.
 *         If the graph is empty, it returns 0.
 */
template<typename T>
int graphColoringFree(Graph<T>* g) {
    int biggestColor=0;
    std::vector<bool>usedColors(0,false);
    for (int i=0;i<usedColors.size();i++) {
        usedColors[i] = false;
    }
    if (g->getVertexSet().size()>0) {
        biggestColor=0;
        for (auto &v:g->getVertexSet()) {
            v->setVisited(false);
            v->setNum(-1);
        }

        for (int k=0;k<g->getVertexSet().size();k++) {
            if (!g->getVertexSet()[k]->isVisited()){
                graphColoringFree(g->getVertexSet()[k],biggestColor,usedColors);
            }
        }
    }

    return biggestColor;

}


/**
 * @brief Applies the given greedy graph coloring algorithm but without spilling properly.
 * The time complexity is O(|V|^2) and the space complexity is O(V)
 *
 * @details This algorithm attempts to color an undirected graph, ensuring that no
 * pair of adjacent vertices share the same color, using a maximum of N colors.
 * The algorithm is divided into two phases:
 * - Phase 1 (Simplification): Iteratively removes nodes with a degree less than N
 *   and pushes them onto a stack.
 * - Phase 2 (Coloring): Pops nodes from the stack and assigns the lowest available
 *   color (0-indexed) that is not currently used by its already-colored neighbors.
 *
 *
 * @tparam T The data type stored within the vertex (e.g., int, std::string).
 *
 * @param g Pointer to the Graph object to be colored. The graph must have
 *          bidirectional (undirected) edges for the degree calculation to work correctly.
 * @param N The maximum number of allowed colors (the heuristic's limit).
 *
 * @return Returns the total number of colors used to color the graph.
 *         Returns -1 if the algorithm fails to find a node with degree < N
 *         during the simplification phase (a "spill" condition).
 */
template<typename T>
int graphColoringBasic(Graph<T>* g,unsigned int N) {
    std::vector<Vertex<T>*>stack;
    for (auto v:g->getVertexSet()) {
        v->setVisited(false);
        v->setIndegree(v->getAdj().size());
    }
    int n_nodes=g->getVertexSet().size();
    bool all_remaining_nodes_degree_eq_gt_N=true;
    while (n_nodes>0) {
        for (auto v:g->getVertexSet()) {
            if (!v->isVisited()) {
                if (v->getIndegree()<N) {
                    n_nodes--;
                    stack.push_back(v);
                    v->setVisited(true);
                    for (auto e:v->getAdj()) {
                        Vertex<T>* w=e->getDest();
                        w->setIndegree(w->getIndegree()-1);
                    }
                }
            }
        }
        all_remaining_nodes_degree_eq_gt_N=true;
        for (auto v:g->getVertexSet()) {
            if (!v->isVisited()) {
                if (v->getIndegree()<N) {
                    all_remaining_nodes_degree_eq_gt_N=false;
                }
            }
        }
        if (n_nodes!=0 && all_remaining_nodes_degree_eq_gt_N) {
            return -1;
        }
    }

    for (auto &v:g->getVertexSet()) {
        v->setVisited(false);
        v->setNum(-1);
    }



    int biggestColor=-1;
    std::vector<bool>usedColors(N,0);

    while (!stack.empty()) {
        Vertex<T>* v=stack.back();
        stack.pop_back();
        for (auto e:v->getAdj()) {
            Vertex<T>*w=e->getDest();
            if (w->getNum()!=-1) {
                usedColors[w->getNum()]=true;
            }
        }

        for ( int i=0;i<N;i++) {
            if (!usedColors[i]) {
                v->setNum(i);
                biggestColor=std::max(i,biggestColor);
                break;
            }
        }
        for ( unsigned int i=0;i<N;i++) {
            usedColors[i] = false;
        }
    }

    return biggestColor+1;


}


/*
template<typename T>
int graphColoring(Graph<T>* g) {
    int biggestColor=0;
    std::vector<bool>usedColors(g->getVertexSet().size(),0);
    for (int i=0;i<usedColors.size();i++) {
        usedColors[i] = false;
    }
    if (usedColors.size()>0) {
        biggestColor=1;
        for (auto &v:g->getVertexSet()) {
            v->setVisited(false);
            v->setNum(-1);
        }
        std::vector<Vertex<T>*>fila;
        for (int k=0;k<g->getVertexSet().size();k++) {
            if (!g->getVertexSet()[k]->isVisited()){
                fila.push_back(g->getVertexSet()[k]);
                while (!fila.empty()) {
                    Vertex<T>*v=fila.front();
                    fila.erase(fila.begin());
                    v->setVisited(true);
                    for (int i=0;i<biggestColor;i++) {
                        usedColors[i] = false;
                    }
                    for (auto &e:v->getAdj()) {
                        Vertex<T>*w=e->getDest();
                        if (w->getNum()!=-1) {
                            usedColors[w->getNum()]=true;
                        }
                        if (!w->isVisited()) {
                            fila.push_back(w);
                            w->setVisited(true);
                        }
                    }
                    int i=0;

                    for (const auto &c:usedColors) {

                        if (!c) {
                            v->setNum(i);
                            break;
                        }
                        i++;
                    }
                    biggestColor=std::max(biggestColor,i+1);
                }
            }
        }
    }

    return biggestColor;

}*/


#endif //PROJETO2_GRAPHCOLORING_H