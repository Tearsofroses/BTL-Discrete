#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 1e5 + 5;
void BF(int G[20][20], int numberOfVertices, char startVertex, int BFValue[20], int BFPrev[20]);
string BF_Path(int G[20][20], int numberOfVertices, char startVertex, char goalVertex) ;