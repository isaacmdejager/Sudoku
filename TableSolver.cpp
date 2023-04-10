#include <iostream>
#include <ctime>

#include "TableGenerator.h"
#include "MinimizeMarks.h"
#include "Search.h"

using namespace std;

bool tableSolved() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (marks[i][j].size() != 1) {
                return false;
            }
        }
    }

    return true;

}

bool tableBroken() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (marks[i][j].size() == 0) {
                return true;
            }
        }
    }

    return false;

}

void setValue(int a, int row, int col) {

    marks[row][col].clear();
    marks[row][col].push_back(a);
    table[row][col] = a;

}

void fillTable() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for(int k = 1; k < 10; k++) {
                marks[i][j].push_back(k);
            }
        }
    }

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

//Given a cell, if there is only one mark placed in that cell then place it
bool singleCandidate(int row, int col) {



}

//Given a cell with mark X, if X is elimated from the marks in all other cells on that row,
//then set X to the cell in that table.
//Same applies to a cell's column and block.
//Return true if X can be set. Otherwise return false.
bool elimination(int row, int col) {

    int a;
    for (int i = 0; i < marks[row][col].size(); i++) {

        a = marks[row][col][i];
        if (
            !searchMarksRow(a, row, col) ||
            !searchMarksCol(a, row, col) ||
            !searchMarksBlock(a, row, col)
        ) {
            setValue(a, row, col);
            return true;
        }

    }

    return false;
    
}

bool solveTable() {

    cutMarks();

    int stoppedAt = 0;
    int j;

    //Loop through all 81 cells, checking at every one to see if a value can be set
    for (int i = 0; i < 81; i++) {

        j = (stoppedAt + i) % 81;

        //If a new value is set, reset the loop counter and all cut marks
        if (table[j / 9][j % 9] == 0 && (singleCandidate(j / 9, j % 9) || elimination(j / 9, j % 9))) {
            
            i = -1;
            stoppedAt = j;
            cutMarks();

        }

    }

    //Scenario 1: table is solved
    if (tableSolved()) {
        return true;
    }

    //Scenario 2: table is broken
    if (tableBroken()) {
        return false;
    }

    //Scenario 3: table is stuck
    return Nishio();

}

