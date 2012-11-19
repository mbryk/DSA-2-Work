/* 
 * File:   graph.h
 * Author: Mark Bryk
 * ECE 165
 * HW #3
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
    //initial constructor. capacity used for hash table, which grows as more nodes are inserted
    graphClass(int capacity = 100);
    
    //each line of graph file describes two adjacent nodes with a cost
    //function inserts vertex into graph if !exists, and adds adjacent object into adjacency list of source vertex
    void addAdjacent(std::string nId, std::string nId2, int cost);
    
    //called by main.cpp to determine if inputed starting vertex is valid
    bool contains(std::string nId);
    
    //implements dijkstras algorithm
    void shortestPath(std::string startingVertex);
    
    //prints each node of graph in inputted order with shortest distance to source and its path
    void printGraph(std::string OutputFile);
    
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
        int cost;
        myNode* node;
    };
    std::list<myNode*> nodes;
    heap *graphHeap;
    hashTable *hash;
    
    //helper function to print graph
    //recursively determines path to vertex based off previous member of node
    std::string printPath(myNode* node);
    
    //if vertex with nId doesnt exist, add vertex to graph
    //return pointer to vertex
    void *getNode(std::string nId);
};

#endif	/* GRAPH_H */

