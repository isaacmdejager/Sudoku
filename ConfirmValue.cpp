#include <iostream>

#include "TableGenerator.h"
#include "Search.h"
#include "MinimizeMarks.h"

using namespace std;

void setValue(int a, int row, int col) {

    marks[row][col].clear();
    marks[row][col].push_back(a);

    //Upon setting a value, remove that value from the marks in the same
    //row, column and block
    exclusion(a, row, col);

}

//Given a cell, determine if the set of marks has only one element
//If it does, set the value in the table at that cell and return false.
//Otherwise (if has more than one mark) return false.
bool singleCandidate(int row, int col) {

    if (marks[row][col].size() == 1) {
        setValue(marks[row][col][0], row, col);
        return true;
    }

    return false;

}

//Given a cell with mark X, if X is elimated from the marks in all other cells on that row,
//then set X to the cell in that table.
//Same applies to a cell's column and block.
//Return true if X can be set. Otherwise return false.
bool eliminationCandidate(int row, int col) {

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