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
#include "hash.h"

class graphClass {
public:
    graphClass();
    void printGraph();
    void *getNode(int nId);
    void addAdjacent(int nId, int nId2, int cost);
    void shortestPath(int startingVertex);
    int shortestUnknown();
    void updateAdjacents();

private:
    class adjacent;
    class myNode {
    public:
        int id;
        bool known;
        int distance;
        std::list<adjacent> adjList;
    };
    class adjacent{
    public:
        int adjId;
        int cost;
        myNode* node;
    };
    
    std::list<myNode*> nodes;
    heap *graphHeap;
    hashTable *hashish;
       
};

#endif	/* GRAPH_H */

