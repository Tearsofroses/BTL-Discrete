#include <iostream>
#include <string>
using namespace std;

bool visited[20] = {false};
int curr_path[20] = {0};
int final_path[20] = {0};
int curr_dist = 0;
int final_dist = 100000;
int MIN = 100000;
void TSPRec(int level, int numberOfVertices, int G[20][20], char startVertex, int MIN);
string Traveling(int G[20][20], int numberOfVertices, char startVertex);