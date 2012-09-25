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

bool valid(char letter, bool insert = false){
    if((isalnum(letter)) || (letter=='-') || (letter=='\''))
        return true;
    else
        return false;
}
int loadDictionary(ifstream input, hashTable& hasher) {
    char c;
    string word="";
    bool valid = true;
    while (!input.eof())
    {
        input.get(c);
        c = tolower(c);
        if (c == '\n' || input.eof() )
        {
            if(valid==false)
                hasher.insert(word);
            word="";
            
            valid = true;
        }else  {
            valid = valid(c, true);
            word+=c;
        }
    }
    input.close();
}
int spellCheck(ifstream scfile, ofstream output, hashTable& hasher){
    char c;
    string checkit="";
    while (!scfile.eof())
    {
        scfile.get(c);
        if (c == '\n' || c==' ' || scfile.eof() )
        {
            if(!hasher.contains(checkit))
                cout<<"Not in Dictionary. \n";
            checkit="";
        }else  checkit+=c;
    }
    
    scfile.close();
    output.close();
}
int main(int argc, char** argv) {
    hashTable hasher(200);
    
    string Dictionary, SpellCheck, OutputFile;
    cout<<"Enter path of dictionary: ";
    cin>>Dictionary;
    
    ifstream input;
    input.open(Dictionary.c_str());
    loadDictionary(input, hasher);
    
    cout<<"Enter path of file to spell check:";
    cin>>SpellCheck;
            
    cout<<"Enter path of output file: ";
    cin>>OutputFile;
    
    ifstream scfile;
    ofstream output;
    
    scfile.open(SpellCheck.c_str());
    output.open(OutputFile.c_str());

    spellCheck(scfile, output, hasher);
    
    return 0;
}

//cerr
