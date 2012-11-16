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
    void printGraph();
    void addNode(int nId, int nId2, int cost);
    void shortestPath(int startingVertex);
    int shortestUnknown();
    void updateAdjacents(const node &node);

private:
    class adjacent{
    public:
        int adjId;
        int cost;
    };
    class node {
    public:
        int id;
        bool known;
        int distance;
        std::list<adjacent> adjList;
    };
    
    std::list<node> nodes;
    heap *graphHeap;
       
};

#endif	/* GRAPH_H */

