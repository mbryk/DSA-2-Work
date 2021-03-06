/* 
 * File:   main.cpp
 * Author: mark
 *
 * Created on November 9, 2012, 1:59 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <graph.h>
using namespace std;

/*
 * 
 */
int vId(string vertex){
    return vertex.erase(0,1);
}

void loadGraph(string GraphFile, graphClass &graph){
    ifstream input;
    string vertex, vertex2;
    int cost;
    
    input.open(GraphFile.c_str());
    while(!input.eof()){
        input>>vertex>>vertex2>>cost;
        graph.addNode(vId(vertex), vId(vertex2), cost);
    }
}
int main(int argc, char** argv) {
    graphClass graph;
    string GraphFile;
    int StartingVertex;
    
    cout<<"Enter name of graph: ";
    cin>>GraphFile;
    
    clock_t t1 = clock();
    loadGraph(GraphFile, graph);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << timeDiff << endl;    
    
    cout<<"Enter id of starting vertex: ";
    cin>>StartingVertex;
    
    clock_t t3 = clock();
    graph.shortestPath(StartingVertex);
    clock_t t4 = clock();
    double timeDiff2 = ((double) (t4 - t3)) / CLOCKS_PER_SEC;
    
    cout << "Total time (in seconds) to check document: " << timeDiff2 << endl;  
    
    return 0;
}

