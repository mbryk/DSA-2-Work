/* 
 * File:   graph.cpp
 * Author: mark
 * 
 * Created on November 9, 2012, 2:01 PM
 */

#include <iostream>
#include <fstream>
#include <climits>
#include "graph.h"
#include "heap.h"
#include "hash.h"

using namespace std;
graphClass::graphClass() {
    graphHeap = new heap(100);
    hash = new hashTable(100*2);
}
void graphClass::printGraph(string OutputFile){
    ofstream output;
    output.open(OutputFile.c_str());
    
    list<myNode*>::const_iterator iterator;
    string sources;
    
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        output << (*iterator)->id << ": ";
        if((*iterator)->distance == INT_MAX)
            output << "NO PATH" <<endl;
        else{
            sources = printPath(*iterator);
            output<< (*iterator)->distance << " [" << sources << "]"<<endl;
        }
    }
}
string graphClass::printPath(myNode* node){
    string path;
    if(node->previous != NULL) path= printPath(node->previous) + ", ";
    path += node->id; 
    return path;
}

void* graphClass::getNode(string nId){
    myNode *pointer;
    
    pointer = static_cast<myNode *> (hash->getPointer(nId));
    
    if(pointer == NULL){
        pointer = new myNode;
        pointer->id = nId;
        nodes.insert(nodes.end(), pointer);
        hash->insert(nId, pointer);
    }
    return pointer;
}

void graphClass::addAdjacent(string nId1, string nId2, int cost){
    myNode *sourceNode, *edgeNode;
    sourceNode = static_cast<myNode *> (getNode(nId1));
    edgeNode = static_cast<myNode *> (getNode(nId2));
    
    adjacent *newAdj= new adjacent;
    newAdj->node = edgeNode;
    newAdj->cost = cost;
    sourceNode->adjList.insert(sourceNode->adjList.end(), *newAdj);
}

void graphClass::shortestPath(string nId){
    heap graphHeap(nodes.size());
    myNode *node;
    int distance;
    
    list<myNode*>::iterator iterator;

    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if((*iterator)->id == nId){
            (*iterator)->distance = 0;
        }
        else {
            (*iterator)->distance = INT_MAX;
        }
        (*iterator)->known = false;
        (*iterator)->previous = NULL;
        graphHeap.insert((*iterator)->id, (*iterator)->distance, (*iterator));
    }
    
    list<adjacent>::iterator it;
    while(!graphHeap.deleteMin(NULL, NULL, &node)){
        node->known = true;
        for (it = node->adjList.begin(); it != node->adjList.end(); ++it) {
            if(node->distance == INT_MAX){
                continue;
            }
            distance = (*it).cost + node->distance;
            if(distance < (*it).node->distance){
                (*it).node->distance = distance;
                graphHeap.setKey((*it).node->id, distance);
                (*it).node->previous = node;
            }
        }
    }
}
