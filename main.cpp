#include <iostream>
#include <vector>
#include "TableGenerator.h"
#include "TableSolver.h"
#include "MinimizeMarks.h"

using namespace std;

bool matchesSolution() {
    
    int solution[9][9] = 
    {
        {8, 1, 2, 7, 5, 3, 6, 4, 9},
        {9, 4, 3, 6, 8, 2, 1, 7, 5},
        {6, 7, 5, 4, 9, 1, 2, 8, 3},
        {1, 5, 4, 2, 3, 7, 8, 9, 6},
        {3, 6, 9, 8, 4, 5, 7, 2, 1},
        {2, 8, 7, 1, 6, 9, 5, 3, 4},
        {5, 2, 1, 9, 7, 4, 3, 6, 8},
        {4, 3, 8, 5, 2, 6, 9, 1, 7},
        {7, 9, 6, 3, 1, 8, 4, 5, 2}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] != solution[i][j]) {
                return false;
            }
        }
    }

    return true;

}

int main() {

    srand((unsigned) time(NULL));

    generate();

    fillTable();

    solveTable();


    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (marks[i][j].size() == 1) {
                table[i][j] = marks[i][j][0];
            }
        }
    }

    printTable();

    cout << endl;
    cout << "===================" << endl;
    cout << endl;

    cout << matchesSolution() << endl;

}