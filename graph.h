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
    void *getNode(std::string nId);
    void addAdjacent(std::string nId, std::string nId2, int cost);
    void shortestPath(std::string startingVertex);

private:
    class adjacent;
    class myNode {
    public:
        std::string id;
        bool known;
        int distance;
        std::list<adjacent> adjList;
        myNode* previous;
    };
    class adjacent{
    public:
        std::string adjId;
        int cost;
        myNode* node;
    };
    
    std::list<myNode*> nodes;
    heap *graphHeap;
    hashTable *hashish;
       
};

#endif	/* GRAPH_H */

