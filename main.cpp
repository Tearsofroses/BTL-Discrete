#include "tsm.cpp"
#include "bellman.cpp"


int main(){
    int numberOfVertices;
    char startVertex;
    int G[20][20];
    int BFValue[20];
    int BFPrev[20];
    cout << "Enter your graph size: ";
    while (cin >> numberOfVertices) {
        if (numberOfVertices <= 0 || numberOfVertices > 20) {
            cout << "Please enter a number between 0 and 20!" << endl;
            cout << "Enter your graph size: ";
        }
        else break;
    }
    cout << "Enter your start vertex: ";
    while (cin >> startVertex) {
        if (islower((char) startVertex)) startVertex = toupper(startVertex);
        if ((startVertex - 'A' < 0) || startVertex - 'A' >= (numberOfVertices)) {
            cout << "Please enter a plausible starting point!" << endl;
            cout << "Re-Enter your start vertex: ";
        }
        else break;
    }
    cout << "Enter your graph:" << endl;
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            cin >> G[i][j];
        }
    }

    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            cout << G[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "************* RUNNING BELLMAN-FORD ALGORITHM *************" << endl;
    // Run Bellman-Ford algorithm
    for (int i = 0; i < numberOfVertices; i++) {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }
    for (int i = 0 ; i < numberOfVertices; i++) {
        BF(G, numberOfVertices, startVertex, BFValue, BFPrev);

        cout << "Step " << i+1 << ": " <<endl;
        for (int j = 0; j < numberOfVertices; j++) {
            cout << BFValue[j] << " ";
        }
        cout << endl;
        for (int j = 0; j < numberOfVertices; j++) {
            cout << BFPrev[j] << " ";
        }
        cout << endl;
    }
    char start, goal;
    cout << endl << "Enter your desired start vertex to see the BF_Path: ";
    while (cin >> start) {
        if (islower((char) start)) start = toupper(start);
        if ((start - 'A' < 0) || start - 'A' >= (numberOfVertices)) {
            cout << "Please enter a plausible starting point!" << endl;
            cout << "Re-Enter your start vertex: ";
        }
        else break;
    }
    cout << endl << "Enter your desired goal vertex to see the BF_Path: ";
    while (cin >> goal) {
        if (islower((char) goal)) goal = toupper(goal);
        if ((goal - 'A' < 0) || goal - 'A' >= (numberOfVertices)) {
            cout << "Please enter a plausible goal point!" << endl;
            cout << "Re-Enter your goal vertex: ";
        }
        else break;
    }
	cout << "The BF path printed from the above algorithm from " << string(1, start) << " to " << string(1, goal) << " is: ";
    cout << BF_Path(G, numberOfVertices, start, goal);

    cout << endl << "Using the same graph to run TSM." << endl;
    cout << "Enter you starting point for traveling salesman problem: ";
    char new_start;
    while (cin >> new_start) {
        if (islower((char) new_start)) new_start = toupper(new_start);
        if ((new_start - 'A' < 0) || new_start - 'A' >= (numberOfVertices)) {
            cout << "Please enter a plausible goal point!" << endl;
            cout << "Re-Enter your start vertex: ";
        }
        else break;
    }
    cout << endl << "************* RUNNING TRAVELING SALESMAN PROBLEM *************" << endl;
    cout << "Shortest path that covers every points from " << string(1,new_start) << " is " <<  Traveling(G, numberOfVertices, new_start);
	return 0;
}