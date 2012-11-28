/* 
 * File:   merge.cpp
 * Author: Mark Bryk
 * ECE 165
 * HW #4
 *
 * Created on November 28, 2012, 1:45 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string s, print;
int dynamic[1001][1001];
ofstream output;

bool check(int d, char x){
    string local = s;
    int sub = s.size()-d;
    if(sub!=0)
        local = local.erase(0, sub);
    if(x==local[0]) return true;
    else return false;
}
bool printMerge(int i, int j){
    int d = dynamic[i][j];
    int sub = s.size()-d-1;
    if(i==0 && j==0) {
        output<<s<<endl;
        return true;
    }
    if((j!=0) && (dynamic[i][j-1]==d+1)){
        printMerge(i, j-1);
    }
    else if((i!=0)&&(dynamic[i-1][j]==d+1)){
        s[sub] = (char) toupper(s[sub]);
        printMerge(i-1, j);
    }    
    else{
        cerr<<"Sorry. Something has gone wrong.";
        exit(1);
    }
}
void merge(string x, string y, string s){
    int d1, d2;
    
    int n = x.size();
    int m = y.size();
    
    dynamic[0][0]= s.size();
    
    //initialize first column
    for(int a=1;a<=n;a++){
        if(check(dynamic[a-1][0], x[a-1])){
            dynamic[a][0]= dynamic[a-1][0] - 1;
        }
        else
            dynamic[a][0] = dynamic[a-1][0];
    }
    //initialize first row
    for(int b=1;b<=m;b++){
        if(check(dynamic[0][b-1], y[b-1])){
            dynamic[0][b]= dynamic[0][b-1] - 1;
        }
        else
            dynamic[0][b]= dynamic[0][b-1];
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1; j<=m; j++){
            d1 = dynamic[i-1][j];
            d2 = dynamic[i][j-1];
            if(check(d1, x[i-1])){
                d1--;
            }
            if(check(d2, y[j-1])){
                d2--;
            }
            if(d1<d2)
                dynamic[i][j] = d1;
            else
                dynamic[i][j] = d2;
        }
    }
    if(dynamic[n][m]==0) 
        printMerge(n, m);
    else 
        output<<"*** NOT A MERGE ***"<<endl;
}

int main(int argc, char** argv) {
    string InputFile, OutputFile, x, y;

    cout<<"Enter name of input file: ";
    cin>>InputFile;
    cout<<"Enter name of output file: ";
    cin>>OutputFile;

    ifstream input;
    input.open(InputFile.c_str());
    if(!input.is_open()){
        cerr<< "Error while opening " << InputFile << endl;
        exit(1);
    }
    
    output.open(OutputFile.c_str());
    if(!output.is_open()){
        cerr<< "Error while opening " << OutputFile << endl;
        exit(1);
    }

    while(!input.eof()){
        input>>x>>y>>s;
        merge(x, y, s);
    }
    return 0;
}
