#include "spilling.h"

using namespace std;

bool cmp(Vertex<web> * a, Vertex<web> * b){
    if (a->getIndegree() > b->getIndegree()) return true;

    return false;
}

bool incrementGrid(vector<int>& grid, int spilled){
    if (spilled > (int)grid.size()) spilled = (int)grid.size();
    if (spilled == 0) return true;

    if (count(grid.begin(), grid.end(), 1) == 0){ 
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

bool attempt(Graph<web>* g, params info, vector<Vertex<web> *> candidates, int spilled){
    if (spilled == 0){
        for (auto &v : g->getVertexSet()) v->setVisited(false);
        return graphColoring(g) <= info.regs;
    }

    // If we need to spill more than we have candidates, it's impossible in this subset
    if (spilled > (int)candidates.size()) return false;

    vector<int> grid((int)candidates.size(), 0);

    while (!incrementGrid(grid, spilled)){
        for (auto &v : g->getVertexSet()) v->setVisited(false);

        for (int i = 0; i < (int)grid.size(); i++){
            if (grid[i] == 1){
                candidates[i]->setVisited(true);
            }
        }

        if (graphColoring(g) <= info.regs) return true;
    }

    return false;    
}

void finalSpill(Graph<web>* g, params info, vector<Vertex<web> *> candidates, int spilled){
    if (spilled == 0){
        for (auto &v : g->getVertexSet()) v->setVisited(false);
        graphColoring(g);
        return;
    }

    int bestNum = numeric_limits<int>::max();
    vector<int> bestOrder;
    vector<int> grid((int)candidates.size(), 0);

    while (!incrementGrid(grid, spilled)){
        for (auto &v : g->getVertexSet()) v->setVisited(false);

        for (int i = 0; i < (int)grid.size(); i++){
            if (grid[i] == 1) candidates[i]->setVisited(true);
        }

        int newNum = graphColoring(g);
        if (newNum < bestNum){
            bestNum = newNum;
            bestOrder = grid;
        }
    }

    for (auto &v : g->getVertexSet()) v->setVisited(false);
    for (int i = 0; i < (int)bestOrder.size(); i++){
        if (bestOrder[i] == 1) candidates[i]->setVisited(true);
    }
    graphColoring(g);
}

struct result spill(Graph<web>* g, params info){
    vector<Vertex<web> *> vSet = g->getVertexSet();
    sort(vSet.begin(), vSet.end(), cmp);

    // X is the number of 'best' candidates the program will use to try to find the optimal spill. The more candidates, the better the result, but also the longer the program will take to run (exponentially in the number of candidates). It is recommended to set it to a value between 15 and 25.
    int X = 20; 
    vector<Vertex<web> *> candidates;
    for(int i = 0; i < (int)vSet.size() && i < X; i++) {
        candidates.push_back(vSet[i]);
    }

    int maxPossible = min((int)candidates.size(), info.alg.val);
    vector<int> allSpills(maxPossible + 1);
    for (int i = 0; i < (int)allSpills.size(); i++) allSpills[i] = i;

    auto it = std::lower_bound(allSpills.begin(), allSpills.end(), true,
        [&](int spilled, bool target) {
            return !attempt(g, info, candidates, spilled);
        }
    );

    int trueSpills = (it != allSpills.end()) ? *it : -1;

    if (trueSpills != -1){
        finalSpill(g, info, candidates, trueSpills);
    } else {
        finalSpill(g, info, candidates, 0);
    }

    struct result res = build(g, info);
    if (trueSpills == -1) res.possible = false;
    return res;
}