#include <iostream>
#include <cstdlib>

#include "TableGenerator.h"
#include "ConfirmValue.h"
#include "MinimizeMarks.h"

using namespace std;

bool solved() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (marks[i][j].size() != 1) {
                return false;
            }
        }
    }

    return true;

}

bool tableBroke() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (marks[i][j].size() == 0) {
                return true;
            }
        }
    }

    return false;

}

void fillTable() {

    //HARDEST SUDOKU PROBLEM
    setValue(8, 0, 0);
    setValue(3, 1, 2);
    setValue(6, 1, 3);
    setValue(7, 2, 1);
    setValue(9, 2, 4);
    setValue(2, 2, 6);
    setValue(5, 3, 1);
    setValue(7, 3, 5);
    setValue(4, 4, 4);
    setValue(5, 4, 5);
    setValue(7, 4, 6);
    setValue(1, 5, 3);
    setValue(3, 5, 7);
    setValue(1, 6, 2);
    setValue(6, 6, 7);
    setValue(8, 6, 8);
    setValue(8, 7, 2);
    setValue(5, 7, 3);
    setValue(1, 7, 7);
    setValue(9, 8, 1);
    setValue(4, 8, 6);



    // setValue(8, 0, 2);
    // setValue(4, 0, 7);
    // setValue(6, 1, 1);
    // setValue(3, 1, 5);
    // setValue(2, 2, 0);
    // setValue(5, 2, 4);
    // setValue(1, 2, 6);
    // setValue(8, 2, 8);
    // setValue(9, 3, 8);
    // setValue(8, 4, 0);
    // setValue(1, 4, 4);
    // setValue(7, 4, 6);
    // setValue(5, 4, 8);
    // setValue(2, 5, 2);
    // setValue(8, 5, 3);
    // setValue(4, 6, 4);
    // setValue(2, 6, 7);
    // setValue(3, 7, 2);
    // setValue(5, 7, 5);
    // setValue(4, 7, 6);
    // setValue(7, 7, 8);
    // setValue(7, 8, 0);
    // setValue(9, 8, 7);
    


}

bool solveTable() {

    int stoppedAt = 0;
    int j;

    while (cutMarks()) {
    // do {

        for (int i = 0; i < 81; i++) {

            j = (i + stoppedAt) % 81;
            if (marks[j / 9][j % 9].size() > 1 &&
                (singleCandidate(j / 9, j % 9) || eliminationCandidate(j / 9, j % 9))
            ) {
                i = -1;
                stoppedAt = j;
            }

        }

        if (solved()) {
            return true;
        }

        else if(tableBroke()) {
            return false;
        }

    }
    // } while(cutMarks());

    return Nishio();

}

