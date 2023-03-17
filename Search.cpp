#include <iostream>

#include "TableGenerator.h"
#include "MinimizeMarks.h"

using namespace std;

//Search for a mark in a given cell. Return true if found, otherwise return false.
bool searchMarks(int a, int row, int col) {
    return find(marks[row][col].begin(), marks[row][col].end(), a) != marks[row][col].end();
}

//In the marks 2-D array, search the row of the specified cell for a specified vaoue
//The 4th parameter works as follows:
//If remove = false => stop at the first instance of finding the value a and return the bool
//If remove = true => remove all instances of the value a in the row
bool searchMarksRow(int a, int c, int col, bool remove = false) {

    int d;
    for (int i = 1; i < 9; i++) {
        d = (col + i) % 9;
        if (searchMarks(a, c, d)) {
            if (remove) {
                removeMark(a, c, d);
            } else {
                return true;
            }
        }
    }

    return false;

}

//In the marks 2-D array, search the column of the specified cell for a specified vaoue
//The 4th parameter works as follows:
//If remove = false => stop at the first instance of finding the value a and return the bool
//If remove = true => remove all instances of the value a in the column
bool searchMarksCol(int a, int row, int d, bool remove = false) {

    int c;
    for (int i = 1; i < 9; i++) {
        c = (row + i) % 9;
        if (searchMarks(a, c, d)) {
            if (remove) {
                removeMark(a, c, d);
            } else {
                return true;
            }
        }
    }

    return false;

}

//In the marks 2-D array, search the block of the specified cell for a specified vaoue
//The 4th parameter works as follows:
//If remove = false => stop at the first instance of finding the value a and return the bool
//If remove = true => remove all instances of the value a in the block
bool searchMarksBlock(int a, int row, int col, bool remove = false) {

    int c, d;
    for (int i = 0; i < 3; i++) {
        c = row / 3 * 3 + (row + i) % 9 % 3;
        for (int j = (i == 0 ? 1 : 0); j < 3; j++) {
            d = col / 3 * 3 + (col + j) % 9 % 3;
            if (searchMarks(a, c, d)) {
                if (remove) {
                    removeMark(a, c, d);
                } else {
                    return true;
                }
            }
        }
    }

    return false;

}

//Specialized row search that skips the cell's block
bool searchRowMinusBlock(int a, int c, int col, bool remove = false) {

    int d;
    for (int i = 0; i < 6; i++) {
        d = (i + col + 3 - (col % 3)) % 9;
        if (searchMarks(a, c, d)) {
            if (remove) {
                removeMark(a, c, d);
            } else {
                return true;
            }
        }
    }

    return false;

}

//Specialized column search that skips the cell's block
bool searchColMinusBlock(int a, int row, int d, bool remove = false) {

    int c;
    for (int i = 0; i < 6; i++) {
        c = (i + row + 3 - (row % 3)) % 9;
        if (searchMarks(a, c, d)) {
            if (remove) {
                removeMark(a, c, d);
            } else {
                return true;
            }
        }
    }

    return false;

}

//Specialized block search that skips the cell's row
bool searchBlockMinusRow(int a, int row, int col, bool remove = false) {

    int c, d;
    for (int i = 1; i < 3; i++) {
        c = row / 3 * 3 + (row + i) % 9 % 3;
        for (int j = 0; j < 3; j++) {
            d = col / 3 * 3 + (col + j) % 9 % 3;
            if (searchMarks(a, c, d)) {
                if (remove) {
                    removeMark(a, c, d);
                } else {
                    return true;
                }
            }
        }
    }

    return false;

}

//Specialized block search that skips the cell's column
bool searchBlockMinusCol(int a, int row, int col, bool remove = false) {

    int c, d;
    for (int i = 1; i < 3; i++) {
        d = col / 3 * 3 + (col + i) % 9 % 3;
        for (int j = 0; j < 3; j++) {
            c = row / 3 * 3 + (row + j) % 9 % 3;
            if (searchMarks(a, c, d)) {
                if (remove) {
                    removeMark(a, c, d);
                } else {
                    return true;
                }
            }
        }
    }

    return false;

}