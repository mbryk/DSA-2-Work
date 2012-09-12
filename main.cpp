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
#include "hash.h"
using namespace std;

bool addToDictionary(string Dictionary);
int main(int argc, char** argv) {
    string Dictionary, SpellCheck, OutputFile;
    
    cout<<"Enter path of dictionary: ";
    cin>>Dictionary;
    addToDictionary(Dictionary);
    cout<<"Dictionary created.";
    
    cout<<"Enter path of file to spell check:";
    cin>>SpellCheck;
            
    cout<<"Enter path of output file: ";
    cin>>OutputFile;
    
    ifstream scfile;
    ofstream output;
    
    scfile.open(SpellCheck.c_str());
    output.open(OutputFile.c_str());
    
    while (!input.eof())
    {
        input.get(letter);
        if (letter == '\n' || input.eof() )
        {
            word="";
        }else  word+=letter;
    }
    
    scfile.close();
    output.close();
    return 0;
}

bool addToDictionary(string Dictionary) {
    ifstream input;
    char letter;
    hashTable(200) hasher;
    string word="";
    input.open(Dictionary.c_str());
    
    while (!input.eof())
    {
        input.get(letter);
        if (letter == '\n' || input.eof() )
        {
            hasher.insert(word);
            word="";
        }else  word+=letter;
    }
    input.close();
    return true;
}

