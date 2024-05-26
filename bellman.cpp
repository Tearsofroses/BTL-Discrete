//#include <"bellman.h">
#include <bits/stdc++.h> 
using namespace std;
const int MAX_N = 1e5 + 5;


void BF(int G[20][20], int numberOfVertices, char startVertex, int BFValue[20], int BFPrev[20]) {
    static int count = 0;
    if (count == 0){
        int startIndex = startVertex - 'A';
        BFValue[startIndex] = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            BFValue[i] = G[startIndex][i];
            BFPrev[i] = startIndex;
        }
        BFPrev[startIndex] = - 1;
    }
    else {
        for (int u = 0; u < numberOfVertices; u++) {
            for (int v = 0; v < numberOfVertices; v++) {
                if (BFValue[v] != 0 && (BFValue[v] > BFValue[u] + G[u][v])) {
                    BFValue[v] = BFValue[u] + G[u][v];
                    BFPrev[v] = u;
                    break;
                }
            }
        }
    }
    count = (count+1)%numberOfVertices;
}

string BF_Path(const int BFPrev[20], char startVertex, char goalVertex) {
    int currentVertex = goalVertex - 'A';
    string path = "";

    // Check if a path exists from start to goal (no predecessor for goal means no path)
    if (BFPrev[currentVertex] == -1) {
        return "No Path Found";
    }

    // Build the path string by backtracking through predecessors
    while (currentVertex != startVertex - 'A') {
        path = string(1, currentVertex + 'A') + " " + path;
        currentVertex = BFPrev[currentVertex];
    }

    // Add the starting vertex to the path
    path = string(1, startVertex + 'A') + " " + path;
    return path;
}

int main(){
    int G[20][20] = {
        {0, 72, 89, 77, 2, 58, 13, 69,}, // A 0
        {77, 0, 69, 31, 57, 93, 83, 48,}, // B 1 
        {52, 21, 0, 62, 8, 77, 32, 14}, // C 2
        {33, 1, 40, 0, 72, 99, 72, 59}, // D 3
        {89, 24, 1, 61, 0, 12, 78, 63}, // E 4
        {36, 91, 98, 79, 26, 0, 28, 1}, // F 5
        {18, 77, 49, 36, 98, 77, 0, 45}, // G 6
        {75, 9, 59, 7, 77, 65, 45, 0} // H 7
    };

    int numberOfVertices = 8;
    char startVertex = 'D';
    int BFValue[20];
    int BFPrev[20]; 

    // Run Bellman-Ford algorithm
    for(int i=0;i<8;i++){
    BFValue[i]=-1;
    BFPrev[i]=-1;
    }
    for(int i=0;i<8;i++){
        BF(G,numberOfVertices,'D',BFValue,BFPrev);

        cout<<"step"<<i+1<<":"<<endl;
        for(int j=0;j<8;j++){
            cout<<BFValue[j]<<" ";
        }
        cout<<endl;
        for(int j=0;j<8;j++){
            cout<<BFPrev[j]<<" ";
        }
        cout<<endl;
    }
	cout << endl;
    cout<<BF_Path(BFPrev,'A','E');
	return 0;
}
