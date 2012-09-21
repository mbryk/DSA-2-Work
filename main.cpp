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

int main(int argc, char** argv) {
    string Dictionary, SpellCheck, OutputFile;
    
    cout<<"Enter path of dictionary: ";
    cin>>Dictionary;
    
    ifstream input;
    input.open(Dictionary.c_str());
    
    char letter;
    hashTable hasher;
    string word="";
    
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
    cout<<"Dictionary created.";
    
    cout<<"Enter path of file to spell check:";
    cin>>SpellCheck;
            
    cout<<"Enter path of output file: ";
    cin>>OutputFile;
    
    ifstream scfile;
    ofstream output;
    
    scfile.open(SpellCheck.c_str());
    output.open(OutputFile.c_str());
    
    string checkit="";
    while (!scfile.eof())
    {
        scfile.get(letter);
        if (letter == '\n' || letter==' ' input.eof() )
        {
            if(!hasher.contains(checkit))
                cout<<"Not in Dictionary. \n";
            checkit="";
        }else  checkit+=letter;
    }
    
    scfile.close();
    output.close();
    return 0;
}