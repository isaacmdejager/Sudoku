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

    float time = 0;

    // for (int k = 0; k < 100; k++) {

    //     const clock_t c = clock();

        fillTable();

        // for (int i = 0; i < 6; i++) {

        //     marks[0][3].erase(marks[0][3].begin() + 3);
        //     marks[0][5].erase(marks[0][5].begin() + 3);
        //     marks[0][8].erase(marks[0][8].begin() + 3);
        //     // marks[1][3].erase(marks[1][3].begin());
        //     // marks[2][5].erase(marks[2][5].begin());
        //     // marks[6][3].erase(marks[6][3].begin());
        //     marks[6][3].erase(marks[6][3].begin() + 3);
        //     marks[2][3].erase(marks[2][3].begin() + 3);
            
        // }

        // printMarks();
        // cout << endl;
        // cout << endl;

        // NakedSubset(3);
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

        // printTable();

        // cout << float(clock() - c) << endl;

        // time += float(clock() - c);

        // wipeTable();

    // }

    // cout << "============" << endl;
    // cout << float(time / 100) << endl;

}