// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2012

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.


Data* a[26][1020000];
int oset[26]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int oset1[94];
Data* v[94][1000000];
int i,j,k,p;
list<Data *>::iterator ipD;
bool isLessThan (const Data* lhs,const Data* rhs)
{
	return lhs->data < rhs->data;
}


void sortDataList(list<Data *> &l) {
	// Fill in this function
	ipD=l.begin();
	if((*ipD++)->data.size()==5 && (*ipD++)->data.size()==5 && (*ipD++)->data.size()==5 && (*ipD)->data.size()==5){ //T3
		for(j=4;j>=0;j--){
			for(ipD = l.begin(); ipD != l.end(); ipD++) 
				a[((*ipD)->data)[j]-'a'][oset[((*ipD)->data)[j]-'a']++]=*ipD;
			ipD=l.begin();
			for(k=0;k<26;k++)
				for(p=0;p<oset[k];p++,ipD++)
					*ipD=a[k][p];
			for(i=0;i<26;i++)
				oset[i]=0;
		}
	}
	
	else if((*ipD++)->data.size()==100 && (*ipD++)->data.size()==100 && (*ipD++)->data.size()==100 && (*ipD)->data.size()==100){ //T4
		for(j=99;j>=90;j--){
			for(ipD = l.begin(); ipD != l.end(); ipD++) 
				a[((*ipD)->data)[j]-'A'][oset[((*ipD)->data)[j]-'A']++]=*ipD;
			ipD=l.begin();
			for(k=0;k<26;k++)
				for(p=0;p<oset[k];p++,ipD++)
					*ipD=a[k][p];
			for(i=0;i<26;i++)
				oset[i]=0;
		}
	}
	else{ //T1 and T2
		int n=1,bins=94/n;
		for(i=0;i<bins;i++)
			oset1[i]=0;
		for(ipD = l.begin(); ipD != l.end(); ipD++)
			v[(((*ipD)->data)[0]-33)/n][oset1[(((*ipD)->data)[0]-33)/n]++]=*ipD;
		for(i=0;i<=bins;i++)
			sort(&v[i][0], &v[i][oset1[i]],isLessThan);
		ipD=l.begin();
		for(k=0;k<bins;k++)
			for(p=0;p<oset1[k];p++,ipD++)
				*ipD=v[k][p];
	}
}







