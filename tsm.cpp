#include <bits/stdc++.h> 
using namespace std;
const int MAX_N = 1e5 + 5;
// void reverseStr(string& str)
// {
//     int n = str.length();
//     for (int i = 0; i < n / 2; i++)
//         swap(str[i], str[n - i - 1]);
// }

// string BF_Path(int G[20][20], int numberOfVertices, char startVertex, char goalVertex) {
//     int startIndex = startVertex - 'A';
//     int BFValue[20];
//     int BFPrev[20];
//     memset(BFPrev,-1,20);
//     memset(BFValue,-1,20);
//     BFValue[startIndex] = 0;
//     for (int i = 0; i < numberOfVertices; i++) {
//         BFValue[i] = G[startIndex][i];
//         BFPrev[i] = startIndex;
//     }
//     BFPrev[startIndex] = - 1;
//     for (int i = 0; i < numberOfVertices-1; i++) {    
//         for (int u = 0; u < numberOfVertices; u++) {
//             for (int v = 0; v < numberOfVertices; v++) {
//                 if (BFValue[v] != 0 && (BFValue[v] > BFValue[u] + G[u][v])) {
//                     BFValue[v] = BFValue[u] + G[u][v];
//                     BFPrev[v] = u;
//                 }
//             }
//         }
//     }

//     string res = "";
//     int start = startVertex - 'A';
//     int end = goalVertex - 'A';
//     if (start == end) return string(1,startVertex);
//     for (int i = end; i != -1; i = BFPrev[i]) {
//         char temp = 'A';
//         temp += i;
//         res += " " + string(1,temp);
//     }
//     reverseStr(res);
//     return res;
// }

int final_res = MAX_N;
int final_path[20];
int curr_path[20];
bool visited[20];

string final (int numberofVertices, char startVertex)
{
    string sol = "";
    for (int i = 0; i < numberofVertices; i++) {
        char temp = 'A';
        temp += curr_path[i];
        sol += string(1,temp) + " ";
    }
    sol += string(1,startVertex);
    return sol; 
}

void copyToFinal(int curr_path[], int numberofVertices)
{
    for (int i=0; i<numberofVertices; i++)
        final_path[i] = curr_path[i];
    final_path[numberofVertices] = curr_path[0];
}

int firstMin (int G[20][20], int i, int numberofVertices)
{
    int min = MAX_N;
    for (int j = 0; j < numberofVertices; j++) {
        if (G[20][20] < min && i != j) {
            min = G[20][20];
        }

    }
    return min;
}

int secondMin (int G[20][20], int i, int numberofVertices)
{
    int first = MAX_N, second = MAX_N;
    for (int j = 0; j < numberofVertices; j++)
    {
        if (i == j)
            continue;
 
        if (G[i][j] <= first)
        {
            second = first;
            first = G[i][j];
        }
        else if (G[i][j] <= second && G[i][j] != first)
            second = G[i][j];
    }
    return second;
}

void TSPRec (int G[20][20], int curr_bound, int curr_weight, int level, int curr_path[],int numberofVertices)
{
    if (level == numberofVertices) {
        if (G[curr_path[level-1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + G[curr_path[level-1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path,numberofVertices);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < numberofVertices; i++) {
        if (G[curr_path[level-1]][i] != 0 && visited[i] == false) {
            int temp = curr_bound;
            curr_weight += G[curr_path[level-1]][i];

            if (level == 1)
                curr_bound -= ((firstMin(G,curr_path[level-1],numberofVertices)
                                + firstMin(G,i,numberofVertices))/2);
            else 
                curr_bound -= ((secondMin(G,curr_path[level-1],numberofVertices)
                                + firstMin(G,i,numberofVertices))/2);

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(G,curr_bound,curr_weight,level+1,curr_path,numberofVertices);
            }
            curr_weight -= G[curr_path[level-1]][i];
            curr_bound = temp;
            memset(visited,false, numberofVertices);
            for (int j = 0; j <= level - 1; j++)
                visited[curr_path[j]] = true;
        }
    }
}

void TSP (int G[20][20],int numberofVertices)
{
    int curr_path[numberofVertices+1];
    int curr_bound = 0;
    memset(curr_path,-1,numberofVertices);
    memset(visited,0,numberofVertices);

    for (int i = 0; i < numberofVertices; i++)
        curr_bound += (firstMin(G,i,numberofVertices)
                        + secondMin(G,i,numberofVertices));
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 :
                                 curr_bound/2;
    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(G, curr_bound, 0, 1, curr_path,numberofVertices);
}


string Traveling (int G[20][20], int numberofVertices, char startVertex)
{
    return final(numberofVertices,startVertex);
}



int main()
{
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
    //cout << Traveling(G,8,'D');
    TSP(G,8);
    for (int i = 0; i < 8; i++)
        cout << final_path[i] << " ";
    return 0;
}