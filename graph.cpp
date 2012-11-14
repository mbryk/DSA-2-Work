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
    //temporary new node checker....

    list<node>::const_iterator iterator;
    adjacent *newAdj= new adjacent;
    newAdj->adjId = nId2;
    newAdj->cost = cost;
    
    node *newNode;
    bool here;
    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if(iterator->id == nId) {
            here = true;
            iterator->adjList.insert(*iterator->adjList.end(), *newAdj);
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

