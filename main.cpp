#include <iostream>
#include <vector>
#include <ctime>

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

void wipeTable() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            table[i][j] = 0;
            marks[i][j].clear();
        }
    }

}

int main() {

    srand((unsigned) time(NULL));


    for (int k = 0; k < 1; k++) {

        fillTable();

        // for (int i = 0; i < 6; i++) {

        //     marks[0][3].erase(marks[0][3].begin());
        //     marks[0][5].erase(marks[0][5].begin());
        //     marks[0][8].erase(marks[0][8].begin());
        //     // marks[1][3].erase(marks[1][3].begin());
        //     // marks[2][5].erase(marks[2][5].begin());
        //     // marks[6][3].erase(marks[6][3].begin());
            
        // }

        // printMarks();
        // cout << endl;
        // cout << endl;

        // NakedSubset(8);
        // cout << endl;
        // cout << endl;

        // printMarks();



        solveTable();

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (marks[i][j].size() == 1) {
                    table[i][j] = marks[i][j][0];
                }
            }
        }

        printTable();
        // cout << matchesSolution() << endl;

        wipeTable();

    }

   

}