#include "bellman.h"

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
                }
            }
        }
    }
    count = (count+1)%numberOfVertices;
}

void reverseStr(string& str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

string BF_Path(int G[20][20], int numberOfVertices, char startVertex, char goalVertex) 
{
    int startIndex = startVertex - 'A';
    int BFValue[20];
    int BFPrev[20];
    memset(BFPrev,-1,20);
    memset(BFValue,-1,20);
    BFValue[startIndex] = 0;
    for (int i = 0; i < numberOfVertices; i++) {
        BFValue[i] = G[startIndex][i];
        BFPrev[i] = startIndex;
    }
    BFPrev[startIndex] = - 1;
    for (int i = 0; i < numberOfVertices-1; i++) {    
        for (int u = 0; u < numberOfVertices; u++) {
            for (int v = 0; v < numberOfVertices; v++) {
                if (BFValue[v] != 0 && (BFValue[v] > BFValue[u] + G[u][v])) {
                    BFValue[v] = BFValue[u] + G[u][v];
                    BFPrev[v] = u;
                }
            }
        }
    }

    string res = "";
    int start = startVertex - 'A';
    int end = goalVertex - 'A';
    if (start == end) return string(1,startVertex);
    for (int i = end; i != -1; i = BFPrev[i]) {
        char temp = 'A';
        temp += i;
        res += " " + string(1,temp);
    }
    reverseStr(res);
    return res;
}
