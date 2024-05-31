#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX_N = 1e5 + 5;

class TSP
{
private:
    int N,start;
    int G[20][20];
    int minTourCost = MAX_N;
    string tour;
public:
    TSP(int G[20][20], int N, int start);
    ~TSP(){};
    void solve();
    string getTour() {return tour;};
};


bool notIn(int elem, int subset);
vector <int> combinations(int r,int n);
void combinations(int set, int at, int r, int n, vector <int> subsets);
void reverseStr(string& str);