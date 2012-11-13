/* 
 * File:   graph.h
 * Author: mark
 *
 * Created on November 9, 2012, 2:01 PM
 */

#ifndef GRAPH_H
#define	GRAPH_H
#include <list>
#include "heap.h"

class graphClass {
public:
    graphClass();
    void loadGraph();
    int shortestPath(int startingVertex);

private:
    void addNode(int nId, int cost);
    class node {
    public:
        int id;
        class adjList{
            int adjId;
            int cost;
        };
        std::list<adjList> adjLists;
    };
    
    std::list<node> nodes;
    heap *graphHeap;
       
};

#endif	/* GRAPH_H */

