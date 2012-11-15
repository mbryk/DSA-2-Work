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
            cout<< iterator2->adjId << "=" << iterator2->cost << ", ";
        }
        cout<<endl;
    }
}
void graphClass::addNode(int nId, int nId2, int cost){
    //create new node if !node exists{

    list<node>::iterator iterator;
    list<adjacent> adjList;
    node *newNode;
    bool here = false;
    
    adjacent *newAdj= new adjacent;
    newAdj->adjId = nId2;
    newAdj->cost = cost;
    
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if(iterator->id == nId) {
            here = true;
            
            /*adjList = iterator->adjList;
            adjList.insert(adjList.end(), *newAdj);
            (*iterator).adjList = adjList;
            
            *newNode = (*iterator);
            cout<< newNode->id;
            newNode->id = 10;
            cout<< newNode->id;*/
            
            iterator->adjList.insert(iterator->adjList.end(), *newAdj);
        }
    }
    
    if(!here){
        newNode = new node;
        newNode->id = nId;
        newNode->adjList.insert(newNode->adjList.end(), *newAdj);
        nodes.insert(nodes.end(), *newNode);
    }
}

void graphClass::shortestPath(int startingVertex){
    cout<< 0;
}

