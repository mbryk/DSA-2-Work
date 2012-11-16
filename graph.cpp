/* 
 * File:   graph.cpp
 * Author: mark
 * 
 * Created on November 9, 2012, 2:01 PM
 */

#include <iostream>
#include "graph.h"
#include "heap.h"

using namespace std;
graphClass::graphClass() {
    
}
void graphClass::printGraph(){
    list<node>::const_iterator iterator;
    list<adjacent>::const_iterator iterator2;
    list<adjacent> adjList;
    
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        cout << iterator->id << " with adjacents: ";
        adjList = iterator->adjList;
        for (iterator2 = adjList.begin(); iterator2 != adjList.end(); ++iterator2) {
            cout<< iterator2->adjId << " cost=" << iterator2->cost << ", ";
        }
        cout<<endl;
    }
}

void graphClass::addNode(int nId, int nId2, int cost){
    //create new node if !node exists{

    list<node>::iterator iterator;
    node *newNode;
    bool here = false;
    
    adjacent *newAdj= new adjacent;
    newAdj->adjId = nId2;
    newAdj->cost = cost;
    
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if(iterator->id == nId) {
            here = true;
            
            iterator->adjList.insert(iterator->adjList.end(), *newAdj);
        }
    }
    
    if(!here){
        newNode = new node;
        newNode->id = nId;
        newNode->known = false;
        newNode->distance = 1000;
        newNode->adjList.insert(newNode->adjList.end(), *newAdj);
        nodes.insert(nodes.end(), *newNode);
    }
}

void graphClass::shortestPath(int s){
    list<node>::iterator iterator;
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if(iterator->id == s){
            iterator->known = true;
        }
    }
}

int graphClass::shortestUnknown(){
    list<node>::iterator iterator;
    node *node;
    int shortest = 1000;
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if(iterator->known == false){
            if(iterator->distance < shortest){
                shortest = iterator->distance;
                *node = (*iterator);
            }
        }
    }
    if(!node) return false;
    else {
        node->known = true;
        graphClass::updateAdjacents(node);
        return true;
    }
}

void graphClass::updateAdjacents(const node &node){
    list<adjacent>::iterator iterator;
    for (iterator = node->adjList.begin(); iterator != node->adjList.end(); ++iterator) {
        if((iterator->cost + node->distance)<(iterator->node.distance))
            iterator->node.distance = iterator->cost + node->distance;
    }
}


