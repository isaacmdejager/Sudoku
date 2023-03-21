#include <iostream>

#include "TableGenerator.h"
#include "ConfirmValue.h"
#include "MinimizeMarks.h"

using namespace std;

bool solved() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] == 0 || marks[i][j].size() != 1) {
                return false;
            }
        }
    }

    return true;

}

void fillTable() {

    // setValue(8, 0, 0);
    // setValue(3, 1, 2);
    // setValue(6, 1, 3);
    // setValue(7, 2, 1);
    // setValue(9, 2, 4);
    // setValue(2, 2, 6);
    // setValue(5, 3, 1);
    // setValue(7, 3, 5);
    // setValue(4, 4, 4);
    // setValue(5, 4, 5);
    // setValue(7, 4, 6);
    // setValue(1, 5, 3);
    // setValue(3, 5, 7);
    // setValue(1, 6, 2);
    // setValue(6, 6, 7);
    // setValue(8, 6, 8);
    // setValue(8, 7, 2);
    // setValue(5, 7, 3);
    // setValue(1, 7, 7);
    // setValue(9, 8, 1);
    // setValue(4, 8, 6);
    


}

void solveTable() {

    int stoppedAt = 0;
    int j;

    do {
        for (int i = 0; i < 81; i++) {

            j = (i + stoppedAt) % 81;
            if (table[j / 9][j % 9] == 0 && 
                (singleCandidate(j / 9, j % 9) || eliminationCandidate(j / 9, j % 9))
            ) {
                i = -1;
                stoppedAt = j;
            }

        }

    } while(cutMarks());

    cout << endl;
    cout << "===================" << endl;
    cout << endl;

    printTable();

    cout << endl;
    cout << "===================" << endl;
    cout << endl;

    printMarks();

}

