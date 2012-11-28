#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
string s;
bool check(int d, char x){
    int sub = s.size()-d;
    s = s.substr(sub, s.size());
    if(x==s[0]) return true;
    else return false;
}
int main(int argc, char** argv) {
    int d1,d2;
    string x, y;
    cin>>x>>y>>s;
    int n = x.length();
    int m = y.length();
    
    int dynamic[n+1][m+1];
    
    dynamic[0][0]= s.length();
    
    //initialize first column
    for(int a=1;a<=n;a++){
        if(check(dynamic[a-1][0], x[a])){
            dynamic[a][0]= dynamic[a-1][0] - 1;
        }
    }
    //initialize first row
    for(int b=1;b<=m;b++){
        if(check(dynamic[0][b-1], y[b])){
            dynamic[0][b]= dynamic[0][b-1] - 1;
        }
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1; j<=m; j++){
            d1 = dynamic[i-1][j];
            d2 = dynamic[i][j-1];
            if(check(d1, x[i])){
                d1--;
            }
            if(check(d2, y[j])){
                d2--;
            }
            if(d1<d2)
                dynamic[i][j] = d1;
            else
                dynamic[i][j] = d2;
        }
    }
    if(dynamic[n][m]==0) cout<<"Merge Works!";
    else cout<<"Not a good merge";
    return 0;
}

