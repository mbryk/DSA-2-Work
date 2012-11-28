#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
string s, print;
int dynamic[1000][1000];

bool check(int d, char x){
    string local = s;
    int sub = s.size()-d;
    if(sub!=0)
        local = local.erase(0, sub);
    if(x==local[0]) return true;
    else return false;
}

//Arrays are passed by default by reference. So I don't believe this is a waste of space.
bool printMerge(int i, int j){
    int d = dynamic[i][j];
    int sub = s.size()-d;
    if(i==0 && j==0) {
        cout<<s;
        return 1;
    }
    if((i!=0)&&(dynamic[i-1][j]==d+1)){
        s[sub] = (char) toupper(s[sub]);
        printMerge(i-1, j);
    }
    else if((j!=0) && (dynamic[i][j-1]==d+1)){
        printMerge(i, j-1);
    }
    else
        return 0;
}

int main(int argc, char** argv) {
    int d1,d2;
    bool found;
    string x, y;
    cin>>x>>y>>s;
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
                found = true;
                d1--;
            }
            if(check(d2, y[j-1])){
                found = true;
                d2--;
            }
            if(!found){
                cout<<"*** NOT A MERGE ***";
                exit(1);
            }
            if(d1<d2)
                dynamic[i][j] = d1;
            else
                dynamic[i][j] = d2;
        }
    }
    if(dynamic[n][m]==0) 
        printMerge(n, m);
    else cout<<"*** NOT A MERGE ***";
    
    return 0;
}
