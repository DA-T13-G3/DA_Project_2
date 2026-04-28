//
// Created by gustavobastos on 27/04/26.
//

#ifndef PROJETO2_GRAPHCOLORING_H
#define PROJETO2_GRAPHCOLORING_H

#include "graph.h"
#include "unordered_map"

int graphColoringTestSuite();

template<typename T>
void graphColoring(Vertex<T>* v,int& biggestColor,std::vector<bool>&usedColors) {
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

    for (const auto &c:usedColors) {
        if (!c) {
            v->setNum(i);
            break;
        }
        i++;
    }
    biggestColor=std::max(biggestColor,i+1);

    for (auto &e:v->getAdj()) {
        Vertex<T>*w=e->getDest();
        if (!w->isVisited()) {
            w->setVisited(true);
            graphColoring(w,biggestColor,usedColors);
        }
    }
}

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

        for (int k=0;k<g->getVertexSet().size();k++) {
            if (!g->getVertexSet()[k]->isVisited()){
                graphColoring(g->getVertexSet()[k],biggestColor,usedColors);
            }
        }
    }

    return biggestColor;

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