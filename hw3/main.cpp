/* 
 * File:   main.cpp
 * Author: Mark Bryk
 * ECE 165
 * HW #3
 *
 * Created on November 9, 2012, 1:59 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"
using namespace std;

void loadGraph(string GraphFile, graphClass &graph){
    ifstream input;
    string vertex, vertex2;
    int cost;
    
    input.open(GraphFile.c_str());
    if(input.is_open()){
        while(!input.eof()){
            input>>vertex>>vertex2>>cost;
            graph.addAdjacent(vertex, vertex2, cost);
        }
    } else{
        cerr<< "Error while opening " << GraphFile << endl;
        exit(1);
    }
}

int main(int argc, char** argv) {
    graphClass graph(100);
    string GraphFile, OutputFile, StartingVertex;
    bool valid = false;
    
    cout<<"Enter name of graph file: ";
    cin>>GraphFile;
    loadGraph(GraphFile, graph);
    
    while(!valid){
        cout<<"Enter a valid vertex id for the starting vertex: ";
        cin>>StartingVertex;
        valid = graph.contains(StartingVertex);
    }
    
    clock_t t1 = clock();
    graph.shortestPath(StartingVertex);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;  
    
    cout<<"Enter name of output file: ";
    cin>>OutputFile;
    graph.printGraph(OutputFile);

    return 0;
}
