#include "createGraph.h"

Graph<web>create(params info){
    Graph<web>newGraph;

    for( web w :info.webs){
        newGraph.addVertex(w);
    }

    int i=0,j=0;

    for (web a :info.webs){

        for (web b :info.webs){

            if(i==j){j++;continue;}

            if(interfere(a,b)){
                newGraph.addBidirectionalEdge(a,b,0);
            }
            j++;
        }
        i++;
    }
    return newGraph;
}

bool interfere(web a, web b){//NOTE: only works if web vectors are ordered
    vector<int> intersection;
    set_intersection(a.lines.begin(), a.lines.end(), b.lines.begin(), b.lines.end(), back_inserter(intersection));
    if(intersection.size()==0)return false;

    for (int i :intersection){

        auto startA =find(a.start.begin(),a.start.end(),i);
        auto startB =find(b.start.begin(),b.start.end(),i);
        auto endA =find(a.end.begin(),a.end.end(),i);
        auto endB =find(b.end.begin(),b.end.end(),i);

        if(!((startA!=a.start.end() && endB!=b.end.end()) ||
         (startB!=b.start.end() && endA!=a.end.end()))){
            return true;
        }
    }
    return false;
}