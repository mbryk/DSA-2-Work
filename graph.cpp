/* 
 * File:   graph.cpp
 * Author: Mark Bryk
 * ECE 165
 * HW #3
 * 
 * Created on November 9, 2012, 2:01 PM
 */

#include <iostream>
#include <fstream>
#include <climits>
#include "graph.h"

using namespace std;

graphClass::graphClass(int capacity) {
    hash = new hashTable(capacity*2);
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

bool graphClass::contains(std::string nId){
    return hash->contains(nId);
}

void graphClass::shortestPath(string nId){
    heap graphHeap(nodes.size());
    myNode *node;
    list<myNode*>::iterator iterator;
    int distance;

    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) { //initialize all nodes in list relative to source and insert into heap
        if((*iterator)->id == nId)
            (*iterator)->distance = 0;
        else
            (*iterator)->distance = INT_MAX;
        (*iterator)->previous = NULL;
        graphHeap.insert((*iterator)->id, (*iterator)->distance, (*iterator));
    }
    
    list<adjacent>::iterator it;
    while(!graphHeap.deleteMin(NULL, NULL, &node)){
        if(node->distance == INT_MAX){
            continue; //There is no path from this node. No need to update adjacency list
        }
        for (it = node->adjList.begin(); it != node->adjList.end(); ++it) {
            distance = (*it).cost + node->distance;
            if(distance < (*it).node->distance){
                (*it).node->distance = distance;
                graphHeap.setKey((*it).node->id, distance);
                (*it).node->previous = node;
            }
        }
    }
}

void graphClass::printGraph(string OutputFile){
    ofstream output;
    output.open(OutputFile.c_str());
    if(output.is_open()){
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
        
    } else{
        cerr<< "Error while opening " << OutputFile << endl;
        exit(1);
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
