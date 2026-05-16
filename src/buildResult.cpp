#include "buildResult.h"

struct result build(Graph<web>* g,const params& info) {
    struct result res;
    res.regs = 0;
    res.possible = false;

    map<int, vector<web>> colorGroups;

    for (auto v : g->getVertexSet()) {
        web currentWeb = v->getInfo();
        int color = v->getNum();

        if (v->isVisited()) { //color==-1
            res.spilledWebs.push_back(currentWeb);
        } else {
            res.webs.push_back(currentWeb);
            colorGroups[color].push_back(currentWeb);
            
            if (color >= res.regs) {
                res.regs = color + 1;
            }
        }
    }

    for (int i = 0; i < res.regs; i++) {
        assignment asgn;
        if (colorGroups.count(i)) {
            asgn.webs = colorGroups[i];
        }
        res.assignments.push_back(asgn);
    }

    res.possible = (res.regs <= info.regs && res.regs!=0);
    return res;
}