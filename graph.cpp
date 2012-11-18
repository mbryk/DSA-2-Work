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

void* graphClass::getNode(int nId){
    myNode *pointer;
    
    stringstream s;
    s << nId;
    string strId = s.str();
    
    pointer = hashish->getPointer(strId);
    
    if(pointer == NULL){
        pointer = new myNode;
        pointer->id = nId;
        pointer->known = false;
        pointer->distance = 1000;
        nodes.insert(nodes.end(), pointer);
        hashish->insert(strId, pointer);
    }
    return pointer;
}

void graphClass::addAdjacent(int nId1, int nId2, int cost){
    myNode *sourceNode, *edgeNode;
    sourceNode = getNode(nId1);
    edgeNode = getNode(nId2);
    
    adjacent *newAdj= new adjacent;
    newAdj->node = edgeNode;
    newAdj->cost = cost;
    sourceNode->adjList.insert(sourceNode->adjList.end(), *newAdj);
}

void graphClass::shortestPath(int nId){
    myNode *node;
    stringstream s;
    s << nId;
    string strId = s.str();
    node = hashish->getPointer(strId);
    
    node->known = true;
    node->distance = 0;
    updateAdjacents(nId);
    
    while(shortestUnknown());
    printGraph();
}

int graphClass::shortestUnknown(){
    list<myNode*>::iterator iterator;
    myNode *node;
    int shortest = 1000;
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if((*iterator)->known == false){
            if((*iterator)->distance < shortest){
                shortest = (*iterator)->distance;
                node = (*iterator);
            }
        }
    }
    if(!node) return false;
    else {
        node->known = true;
        graphClass::updateAdjacents(node->id);
        return true;
    }
}

void graphClass::updateAdjacents(int nId){
    myNode *node;
    stringstream s;
    s << nId;
    string strId = s.str();
    node = hashish->getPointer(strId);
    
    list<adjacent>::iterator iterator;
    for (iterator = node->adjList.begin(); iterator != node->adjList.end(); ++iterator) {
        if((iterator->cost + node->distance)< (iterator->node->distance))
            iterator->node->distance = iterator->cost + node->distance;
    }
}


