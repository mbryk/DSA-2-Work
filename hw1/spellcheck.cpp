/* 
 * File:   spellcheck.cpp
 * Author: mark
 *
 * Created on September 10, 2012, 11:49 AM
 * purpose - counts how many words are in a string                        *
*/

#include <iostream>
#include <string>
using namespace std;

int WordCount(string sentence);
int main()
{
    
    string Mystring;
    
    cout << " Type in the string you would like to use: " << endl;
    
    getline(cin, Mystring);          // inputs sentence
    
    cout << " Your string is: " << Mystring << endl;
    
    
    
    cout << " The string has " << WordCount(Mystring) << " words " << endl;
    
    
    system("pause");
    return 0;
}


// counts the words
int WordCount(string Sentence)
{
    int length = Sentence.length();        // gets lenght of sentence and assines it to int length
   
    int words = 1;                          
  
    
    for (int size = 0; length > size; size++)
    {
                 
        if (Sentence[size] == ' '/*space*/)
        words++;                   // ADDS TO words if there is a space
    }
    if ( Sentence[0] == ' '/*space*/ )
      words--; 
    return words;
}

