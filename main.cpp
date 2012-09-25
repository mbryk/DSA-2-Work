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

bool valid_char(char letter){
    if((isalnum(letter)) || (letter=='-') || (letter=='\'')){
        return true;
    }else
        return false;
}
/*
int loadDictionary(ifstream input, hashTable & hasher) {
    char c;
    string word="";
    bool valid = true;
    while (!input.eof())
    {
        input.get(c);
        c = tolower(c);
        if (c == '\n' || input.eof() )
        {
            if(valid==true)
                hasher.insert(word);
            word="";
            
            valid = true;
        }else  {
            valid = valid_char(c);
            word+=c;
        }
    }
    input.close();
}
int spellCheck(ifstream scfile, ofstream output, hashTable & hasher){
    char c; int line = 1;
    string checkit="";
    while (!scfile.eof())
    {
        scfile.get(c);
        c = tolower(c);
        if ( (!valid_char(c)) || scfile.eof() )
        {
            if( checkit.size()>0 && checkit.size()<21){
                if(!hasher.contains(checkit))
                    output<<"Unknown Word at line "<<line<<": "<<checkit<<endl;            
            }
            if(c == '\n')
                line++;
            checkit="";
            
        } else {
            if(checkit.size()==20) 
                output<<"Long Word at line "<<line<<", starts: "<<checkit<<endl;
            checkit+=c;
        }
    }
    
    scfile.close();
    output.close();
}
*/
int main(int argc, char** argv) {
    hashTable hasher(15000);
  
    string Dictionary, SpellCheck, OutputFile;
    cout<<"Enter name of dictionary: ";
    cin>>Dictionary;
    
    ifstream input;
    input.open(Dictionary.c_str());
    
    clock_t t1 = clock();
    ////////////////////////////////////////////////////////////////////////
        char c;
    string word="";
    bool valid = true;
    while (!input.eof())
    {
        input.get(c);
        c = tolower(c);
        if (c == '\n' || input.eof() )
        {
            if(valid==true){
                hasher.insert(word);
            }
            word="";
            
            valid = true;
        }else  {
            valid = valid_char(c);
            word+=c;
        }
    }
    
    input.close();
    ////////////////////////////////////////////////////////////////////
    //loadDictionary(input, hasher);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << timeDiff << endl;    
    
    cout<<"Enter name of input file: ";
    cin>>SpellCheck;
            
    cout<<"Enter name of output file: ";
    cin>>OutputFile;
    
    ifstream scfile;
    ofstream output;
    
    scfile.open(SpellCheck.c_str());
    output.open(OutputFile.c_str());
    clock_t t3 = clock();
    ////////////////////////////////////////////////////////////////////////////
    string checkit="";
    int line = 1;
    while (!scfile.eof())
    {
        scfile.get(c);
        c = tolower(c);
        if ( (!valid_char(c)) || scfile.eof() )
        {           
            if( checkit.size()>0 && checkit.size()<21){
                if(!hasher.contains(checkit))
                    output<<"Unknown Word at line "<<line<<": "<<checkit<<endl;            
            }
            if(c == '\n')
                line++;
            checkit="";
            
        } else {
            if(checkit.size()==20) 
                output<<"Long Word at line "<<line<<", starts: "<<checkit<<endl;
            checkit+=c;
        }
    }
    
    scfile.close();
    output.close();
/////////////////////////////////////////////////////////////////////////////////////////    
    //spellCheck(scfile, output, hasher);
    clock_t t4 = clock();
    double timeDiff2 = ((double) (t4 - t3)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << timeDiff2 << endl;  
    
    return 0;
}

//cerr
