#include "createGraph.h"

Graph<web>create(params info){
    Graph<web>newGraph;

    for( web w :info.webs){
        newGraph.addVertex(w);
    }

    int i=0,j=0;
    /*
    for (web a :info.webs){

        for (web b :info.webs){

            if(i==j){j++;continue;}

            if(interfere(a,b)){
                newGraph.addBidirectionalEdge(a,b,0);
            }
            j++;
        }
        i++;
    }*/

    for ( unsigned int i=0; i < info.webs.size();i++ ){

        for ( unsigned int j=i+1; j < info.webs.size();j++ ){

            web&a = info.webs[i];
            web&b = info.webs[j];
            if(interfere(a,b)){
                newGraph.addBidirectionalEdge(a,b,0);
            }
        }
    }
    return newGraph;
}

