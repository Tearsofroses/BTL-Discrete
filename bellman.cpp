#include "bellman.h"

void BF(int G[20][20], int numberOfVertices, char startVertex, int BFValue[20], int BFPrev[20])
{
    int startIndex = startVertex - 'A';
    bool first = 1;
    for (int i = 0; i < numberOfVertices; i++) {
        if (BFValue [i] == 0) first = 0;
    }
    if (first){
        for (int i = 0; i < numberOfVertices; i++) {
            if (G[startIndex][i] == 0) {
                BFValue[i] = -1;
                BFPrev[i] = -1;
            }
            if (G[startIndex][i] != 0) {
                BFValue[i] = G[startIndex][i];
                BFPrev[i] = startIndex;    
            }
        }
        BFValue[startIndex] = 0;
        BFPrev[startIndex] = - 1;
        
    }
    else {
        int* BFValueDup = new int [numberOfVertices];
        for (int i = 0; i < numberOfVertices; i++) {
            BFValueDup[i] = BFValue[i];
        }
        for (int u = 0; u < numberOfVertices; ++u) {
            for (int v = 0; v < numberOfVertices; ++v) {
                if (G[u][v] !=0 && BFValueDup[u] != -1) {
                    if (BFValue[v] == -1 && BFPrev[v] == -1) {
                        BFValue[v] = BFValueDup[u] + G[u][v];
                        BFPrev[v] = u;
                        continue;
                    }    
                    if ((BFValue[v] > BFValueDup[u] + G[u][v])) {
                        BFValue[v] = BFValueDup[u] + G[u][v];
                        BFPrev[v] = u;
                    }
                }
            }
        }
    
        delete[] BFValueDup;
    }
}


string BF_Path(int G[20][20], int numberOfVertices, char startVertex, char goalVertex) 
{
    int startIndex = startVertex - 'A';
    int BFValue[20];
    int BFPrev[20];
    for (int i = 0; i < numberOfVertices; i++) {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }
    for (int i = 0; i < numberOfVertices - 1; i++) {
        BF(G, numberOfVertices, startVertex, BFValue, BFPrev);   
    }
    
    int goalIndex = goalVertex - 'A';
    string path;
    path += goalVertex + string(" ");
    
    while (goalIndex != startVertex - 'A') {
        path = (char) (BFPrev[goalIndex] + 'A') + string(" ") + path;
        goalIndex = BFPrev[goalIndex];
    }
    return path;
}

/*
___________.__                  .__  /\      .___                __                .__   __    __    __    
\__    ___/|  |__ _____    ____ |  |_\(    __| _/____ ______   _/  |_____________  |__| |  | _|  | _|  | __
  |    |   |  |  \\__  \  /    \|  |  \   / __ |/ __ \\____ \  \   __\_  __ \__  \ |  | |  |/ /  |/ /  |/ /
  |    |   |   Y  \/ __ \|   |  \   Y  \ / /_/ \  ___/|  |_> >  |  |  |  | \// __ \|  | |    <|    <|    < 
  |____|   |___|  (____  /___|  /___|  / \____ |\___  >   __/   |__|  |__|  (____  /__| |__|_ \__|_ \__|_ \
                \/     \/     \/     \/       \/    \/|__|                       \/          \/    \/    \/
*/