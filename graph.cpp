/* 
 * File:   graph.cpp
 * Author: mark
 * 
 * Created on November 9, 2012, 2:01 PM
 */

#include <iostream>
#include <sstream>
#include "graph.h"
#include "heap.h"
#include "hash.h"

using namespace std;
graphClass::graphClass() {
    graphHeap = new heap(100);
    hashish = new hashTable(100*2);
}
void graphClass::printGraph(){
    list<myNode*>::const_iterator iterator;
    list<adjacent>::const_iterator iterator2;
    list<adjacent> adjList;
    
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        cout << (*iterator)->id << " with adjacents: ";
        adjList = (*iterator)->adjList;
        for (iterator2 = adjList.begin(); iterator2 != adjList.end(); ++iterator2) {
            cout<< iterator2->adjId << " cost=" << iterator2->cost << ", ";
        }
        cout<<endl;
    }
}

void* graphClass::getNode(string nId){
    myNode *pointer;
    
    pointer = static_cast<myNode *> (hashish->getPointer(nId));
    
    if(pointer == NULL){
        pointer = new myNode;
        pointer->id = nId;
        pointer->known = false;
        pointer->distance = 1000;
        nodes.insert(nodes.end(), pointer);
        hashish->insert(nId, pointer);
    }
    return pointer;
}

void graphClass::addAdjacent(string nId1, string nId2, string cost){
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
    
    list<myNode*>::iterator iterator;

    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        (*iterator)->previous = NULL;
        if((*iterator)->id == nId){
            (*iterator)->distance = 0;
            (*iterator)->known = true;
        }
        else {
            (*iterator)->distance = 1000;
            (*iterator)->known = false;
            graphHeap.insert((*iterator)->id, (*iterator)->distance, (*iterator));
        }
    }
    
    list<adjacent>::iterator it;
    while(graphHeap.deleteMin(NULL, NULL, &node)){
        node->known = true;
        for (it = node->adjList.begin(); it != node->adjList.end(); ++it) {
            if(node->distance == 1000){
                continue;
            }
            distance = (*it)->cost + node->distance;
            if(distance < (*it)->node->distance){
                (*it)->node->distance = distance;
                graphHeap.setKey((*it)->node->id, distance);
                (*it)->node->previous = node;
            }
        }
    }
}
