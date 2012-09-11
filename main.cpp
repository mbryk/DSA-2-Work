/* 
 * File:   main.cpp
 * Author: mark
 *
 * Created on September 6, 2012, 9:11 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <cassert>
using namespace std;

int main(int argc, char** argv) {
    string InputFile, OutputFile;
    
    char letter;
    string word="";
    
    cout<<"Enter path of input file: ";
    cin>>InputFile;
    cout<<"Enter path of output file: ";
    cin>>OutputFile;
    
    ifstream input;
    ofstream output;
    
    input.open(InputFile.c_str());
    output.open(OutputFile.c_str());
    
    while (!input.eof())
    {
        input.get(letter);
        if (letter == '\n' || input.eof() )
        {
            hashTable::insert(word);
            word="";
        }else  word+=letter;
    }
    input.close();
    output.close();
    return 0;
}

