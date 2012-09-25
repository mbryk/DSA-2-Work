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
            if(valid==false)
                hasher.insert(word);
            word="";
            
            valid = true;
        }else  {
            valid = valid_char(c, true);
            word+=c;
        }
    }
    input.close();
}
int spellCheck(ifstream scfile, ofstream output, hashTable & hasher){
    char c;
    string checkit="";
    while (!scfile.eof())
    {
        scfile.get(c);
        c = tolower(c);
        if ( (!valid_char(c)) || scfile.eof() )
        {
            if(!hasher.contains(checkit))
                cout<<"Not in Dictionary. \n";
            checkit="";
        }else  checkit+=c;
    }
    
    scfile.close();
    output.close();
}
*/
int main(int argc, char** argv) {
    hashTable hasher(200);
  
    string Dictionary, SpellCheck, OutputFile;
    cout<<"Enter path of dictionary: ";
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
            if(valid==false)
                hasher.insert(word);
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
    cout << "Dictionary Read. CPU time was " << timeDiff << " seconds." << endl;    

    
    cout<<"Enter path of file to spell check:";
    cin>>SpellCheck;
            
    cout<<"Enter path of output file: ";
    cin>>OutputFile;
    
    ifstream scfile;
    ofstream output;
    
    scfile.open(SpellCheck.c_str());
    output.open(OutputFile.c_str());
    clock_t t3 = clock();
    ////////////////////////////////////////////////////////////////////////////
    string checkit="";
    int line = 0;
    while (!scfile.eof())
    {
        scfile.get(c);
        c = tolower(c);
        if ( (!valid_char(c)) || c==' ' || scfile.eof() )
        {
            if(c == '\n')
                line++;
            else{
                if(checkit.size()>20)
                    cout<<"Long Word on line"<<endl;
                else if(!hasher.contains(checkit))
                    cout<<"Unknown Word on line."<<endl;
            }
            checkit="";
        }else  checkit+=c;
    }
    
    scfile.close();
    output.close();
/////////////////////////////////////////////////////////////////////////////////////////    
    //spellCheck(scfile, output, hasher);
    clock_t t4 = clock();
    double timeDiff2 = ((double) (t4 - t3)) / CLOCKS_PER_SEC;
    cout << "Document Checked. CPU time was " << timeDiff2 << " seconds." << endl;  
    
    return 0;
}

//cerr
