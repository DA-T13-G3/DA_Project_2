#include "spilling.h"

using namespace std;

bool cmp(Vertex<web> * a, Vertex<web> * b){
    if (a->getIndegree() > b->getIndegree()) return true;

    return false;
}

bool incrementGrid(vector<int>& grid, int spilled){
    if (spilled > (int)grid.size()) spilled = (int)grid.size();

    if (count(grid.begin(), grid.end(), 1) == 0){ //auto-initialize
        for (int i = 0; i < spilled; i++){
            grid[i] = 1;
        }
        return false;
    }
    bool moved = false;
    for (int i = 0; i < (int)grid.size()-1; i++){
        if (grid[i+1] == 1) {continue;}
        if (grid[i] == 1){
            moved = true;
            grid[i] = 0;
            grid[i+1] = 1;
            int counter = 0;
            for (int j = 0; j < i; j++){
                if (grid[j] == 1) {counter++;}
                grid[j] = 0;
            }
            for (int k = 0; k < counter; k++){
                grid[k] = 1;
            }
            break;
        }
        
    }

    return !moved;

    
}

bool attempt(Graph<web>* g, params info, vector<Vertex<web> *> vSet, int spilled){

    if (spilled == 0){
        for (auto &v:g->getVertexSet()) {
            v->setVisited(false);
        }
        return graphColoring(g) <= info.regs;
    }

    vector<int> grid((int)vSet.size(), 0);

    while (!incrementGrid(grid, spilled)){
        for (auto &v:g->getVertexSet()) {
            v->setVisited(false);
        }

        for (int i = 0; i < (int)grid.size(); i++){
            if (grid[i] == 1){
                vSet[i]->setVisited(true);
            }
        }

        int newNum = graphColoring(g);

        if (newNum <= info.regs){
            return true;
        }
    }

    return false;    

}

void finalSpill(Graph<web>* g, params info, vector<Vertex<web> *> vSet, int spilled){

    if (spilled == 0){
        for (auto &v:g->getVertexSet()) {
            v->setVisited(false);
        }
        graphColoring(g);
        return;
    }

    int bestNum = numeric_limits<int>::max();
    vector<int> bestOrder;

    vector<int> grid((int)vSet.size(), 0);

    while (!incrementGrid(grid, spilled)){
        for (auto &v:g->getVertexSet()) {
            v->setVisited(false);
        }

        for (int i = 0; i < (int)grid.size(); i++){
            if (grid[i] == 1){
                vSet[i]->setVisited(true);
            }
        }

        int newNum = graphColoring(g);

        if (newNum < bestNum){
            bestNum = newNum;
            bestOrder = grid;
        }
    }

    for (auto &v:g->getVertexSet()) {
        v->setVisited(false);
    }

    for (int i = 0; i < (int)bestOrder.size(); i++){
        if (bestOrder[i] == 1){
            vSet[i]->setVisited(true);
        }
    }

    graphColoring(g);


}

struct result spill(Graph<web>* g, params info){

    vector<Vertex<web> *> vSet = g->getVertexSet();

    sort(vSet.begin(), vSet.end(), cmp);

    vector<int> allSpills(info.alg.val+1);
    for (int i = 0; i < (int)allSpills.size(); i++){
        allSpills[i] = i;
    }

    auto it = std::lower_bound(allSpills.begin(), allSpills.end(), true,
        [&](int spilled, bool target) {

            return !attempt(g, info, vSet, spilled);
        }
    );

    int trueSpills;

    if (it != allSpills.end()) {
        trueSpills = *it;
    } else {
        trueSpills = -1;
    }

    if (trueSpills != -1){
        finalSpill(g, info, vSet, trueSpills);
    } else {
        finalSpill(g, info, vSet, 0);
    }

    struct result res;
    res = build(g, info);
    return res;
}