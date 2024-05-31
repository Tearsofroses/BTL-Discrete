#include "tsm.h"

void reverseStr(string& str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

TSP::TSP(int G[20][20], int N, int start)
    : N(N), start(start)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            this->G[i][j] = G[i][j];
        }
    }

}

void TSP::solve()
{
    int END_STATE = (1 << N) - 1;
    int memo[N][1 << N];
    for (int end = 0; end < N; end++) {
        if (end == start) continue;
        memo[end][(1<<start) | (1<<end)] = G[start][end]; 
    }

    for (int r = 3; r <= N; r++) {
        for (int subset : combinations(r,N)) {
            if (notIn(start,subset)) continue;
            for (int next = 0; next < N; next++) {
                if (next == start || notIn(next,subset)) continue;
                int subsetWithoutNext = subset^(1 << next);
                int min_dist = MAX_N;
                for (int end = 0; end < N; end++) {
                    if (end == start || end == next || notIn(end,subset)) continue;
                    int newDistance = memo[end][subsetWithoutNext] + G[end][start];
                    if (newDistance < min_dist) 
                        min_dist = newDistance;
                }
                memo[next][subset] = min_dist;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (i == start) continue;
        int tourCost = memo[i][END_STATE] + G[i][start];
        if (tourCost < minTourCost) minTourCost = tourCost;
    }

    int lastIndex = start;
    int state = END_STATE;
    tour += string(1,'A'+start) + " ";

    for (int i = 1; i < N; i++) {
        int bestIndex = -1;
        int bestDist = MAX_N;
        for (int j = 0; j < N; j++) {
            if (j == start || notIn(j,state)) continue;
            int newDist = memo[j][state] + G[j][lastIndex];
            if (newDist < bestDist) {
                bestDist = newDist;
                bestIndex = j;
            }
        }
        tour += string(1,bestIndex + 'A') + " ";
        state = state ^ (1 << bestIndex);
        lastIndex = bestDist;
    }
    
    tour += string(1,start + 'A');
    reverseStr(tour);
}

bool notIn(int elem, int subset)
{
    return ((1 << elem) & subset) == 0;
}

vector <int> combinations(int r,int n)
{
    vector <int> subsets;
    combinations(0,0,r,n,subsets);
    return subsets;
}

void combinations(int set, int at, int r, int n, vector <int> subsets)
{
    int elementLeft = n - at;
    if (elementLeft < r) return;
    if (r == 0) subsets.push_back(set);
    else {
        for (int i = at; i < n; i++) {
            set ^= (1<<i);
            combinations(set,i+1,r-1,n,subsets);
            set ^= (1<<i);
        }
    }
}

int main()
{
    int n = 8;
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

    int startNode = 0;
    TSP s1 = TSP(G,n,0);
    s1.solve();
    cout << s1.getTour();
    return 0;
}