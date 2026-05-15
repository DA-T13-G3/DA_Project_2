#include "splitting.h"

void split(Graph<web> *g, params&info){
    //choose vertex to split
    int maxDegree=-1;
    Vertex<web>*maxVertex = nullptr;

    for (auto v : g->getVertexSet()){
        bool allAreStartOrEnd = true;
        for (int line : v->getInfo().lines) {
            bool isStart = find(v->getInfo().start.begin(),v->getInfo().start.end(),line) != v->getInfo().start.end();
            bool isEnd = find(v->getInfo().end.begin(),v->getInfo().end.end(),line) != v->getInfo().end.end();

            if (!isStart && !isEnd) {
                allAreStartOrEnd = false;
                break;
            }
        }

    if (allAreStartOrEnd)
        continue;

        int degree=v->getAdj().size();

        if (maxDegree<degree){
            maxDegree=degree;
            maxVertex=v;
        }
    }

    if (maxVertex == nullptr) {
        return; // nothing to split
    }


    //split the web in 2
    web splitWeb=maxVertex->getInfo(),web1,web2;
    
    web1.var_name=splitWeb.var_name;
    web1.id=splitWeb.id+".0";

    web2.var_name=splitWeb.var_name;
    web2.id=splitWeb.id+".1";

    int value = splitWeb.lines.size() / 2;
    while(1){
        auto start =find(splitWeb.start.begin(),splitWeb.start.end(),splitWeb.lines[value]);
        auto end =find(splitWeb.end.begin(),splitWeb.end.end(),splitWeb.lines[value]);
        if (start==splitWeb.start.end() && end==splitWeb.end.end()){
            for(int i=0; i<splitWeb.lines.size();i++){
                if(i<value){
                    web1.lines.push_back(splitWeb.lines[i]);
                    auto start =find(splitWeb.start.begin(),splitWeb.start.end(),splitWeb.lines[i]);
                    auto end =find(splitWeb.end.begin(),splitWeb.end.end(),splitWeb.lines[i]);
                    if(start!=splitWeb.start.end()){
                        web1.start.push_back(splitWeb.lines[i]);
                    }
                    if(end!=splitWeb.end.end()){
                        web1.end.push_back(splitWeb.lines[i]);
                    }
                }
                else if(i>value){
                    web2.lines.push_back(splitWeb.lines[i]);
                    auto start =find(splitWeb.start.begin(),splitWeb.start.end(),splitWeb.lines[i]);
                    auto end =find(splitWeb.end.begin(),splitWeb.end.end(),splitWeb.lines[i]);
                    if(start!=splitWeb.start.end()){
                        web2.start.push_back(splitWeb.lines[i]);
                    }
                    if(end!=splitWeb.end.end()){
                        web2.end.push_back(splitWeb.lines[i]);
                    }
                }
                else{
                    web1.lines.push_back(splitWeb.lines[i]);
                    web2.lines.push_back(splitWeb.lines[i]);
                    web1.end.push_back(splitWeb.lines[i]);
                    web2.start.push_back(splitWeb.lines[i]);
                }
            }
            break;
        }

        if(value<splitWeb.lines.size()-1)value++;

        else value=0;
    }

    //update params.webs
    for (int i = 0; i < info.webs.size(); i++) {
        if (info.webs[i].lines == splitWeb.lines &&
            info.webs[i].var_name == splitWeb.var_name) {

            info.webs.erase(info.webs.begin() + i);
            info.webs.insert(info.webs.begin() + i, web2);
            info.webs.insert(info.webs.begin() + i, web1);
            break;
        }
    }

    //create 2 new vertices
    g->addVertex(web1);
    g->addVertex(web2);

    //connect to interferences
    for(auto e :maxVertex->getAdj()){
        if(interfere(web1,e->getDest()->getInfo())){
            g->addBidirectionalEdge(web1,e->getDest()->getInfo(),0);
        }
        if(interfere(web2,e->getDest()->getInfo())){
            g->addBidirectionalEdge(web2,e->getDest()->getInfo(),0);
        }
    }

    //delete the old vertex
    g->removeVertex(splitWeb);
}



int splitting(Graph<web> *g, params&info){ 
    //NOTE: maybe change from free to basic later
    int numColors;

    for(int i=0; i<=info.alg.val; i++){

        for (auto v : g->getVertexSet()) {
            v->setVisited(false);
            v->setNum(-1);
        }

        numColors=graphColoringBasic(g,info.regs);
        if(numColors<=info.regs && numColors!=-1){
            return numColors;
        }

        if(i!=info.alg.val)split(g,info);
    }
    if(numColors>info.regs)return -1;
    return numColors;
}