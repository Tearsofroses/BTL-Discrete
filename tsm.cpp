#include "tsm.h"

string PrintResult(int numberOfVertices, char startVertex, int final_path[])
{
    string ans = "";
    for (int i = 0; i < numberOfVertices; i++) {
        ans += string(1,'A' + final_path[i]) + " ";
    }
    ans += string(1,startVertex);
    return ans;
}

void TSPRec(int level, int numberOfVertices, int G[20][20], char startVertex, int MIN)
{
    for (int i = 0; i < numberOfVertices; i++) {
        if (visited[i] == 0) {
            visited[i] = 1;
            curr_path[level] = i;
            curr_dist += G[curr_path[level - 1]][curr_path[level]];
            if (level == numberOfVertices - 1) {
                if (final_dist > curr_dist + G[curr_path[numberOfVertices-1]][startVertex - 'A']) {
                    if (G[curr_path[numberOfVertices-1]][startVertex - 'A'] != 0 && G[curr_path[level - 1]][curr_path[level]] != 0) {
                        final_dist = curr_dist + G[curr_path[numberOfVertices-1]][startVertex - 'A'];
                        for (int j = 0; j < numberOfVertices; j++)
                            final_path[j] = curr_path[j];
                    }
                    
                }
            }
            else if (curr_dist + (numberOfVertices)*MIN  < final_dist) {
                if (G[curr_path[level-1]][curr_path[level]] != 0)
                    TSPRec(level + 1, numberOfVertices, G, startVertex, MIN);
            }

            visited[i] = 0;
            curr_dist -= G[curr_path[level - 1]][curr_path[level]];
        }
    }
}

string Traveling(int G[20][20], int numberOfVertices, char startVertex)
{
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            if (G[i][j] != 0)
                MIN = min(MIN, G[i][j]);
        }
    }
    curr_path[0] = startVertex - 'A';
    visited[startVertex - 'A'] = 1;
    TSPRec(1, numberOfVertices, G, startVertex, MIN);
    string result = PrintResult(numberOfVertices, startVertex, final_path);
    for (int i = 0; i < numberOfVertices; i++) {
        curr_path[i] = 0;
        final_path[i] = 0;
        visited[i] = 0;
    }
    curr_dist = 0;
    final_dist = 100000;
    return result;
}