#include <iostream>

#include "TableGenerator.h"
#include "MinimizeMarks.h"

using namespace std;

//In the table, search the row of the specified cell for a specified value
//Return true if the value is found. Otherwise, return false.
bool searchTableRow(int a, int row, int col) {

    int c, d;
    for (int i = 1; i < 9; i++) {
        c = row;
        d = (col + i) % 9;
        if (table[c][d] == a) {
            return true;
        }
    }

    return false;

}

//In the table, search the column of the specified cell for a specified value
//Return true if the value is found. Otherwise, return false.
bool searchTableCol(int a, int row, int col) {

    int c, d;
    for (int i = 1; i < 9; i++) {
        c = (row + i) % 9;
        d = col;
        if (table[c][d] == a) {
            return true;
        }
    }

    return false;

}

//In the table, search the block of the specified cell for a specified value
//Return true if the value is found. Otherwise, return false.
bool searchTableBlock(int a, int row, int col) {

    int c, d;
    for (int i = 0; i < 3; i++) {
        for (int j = (i == 0 ? 1 : 0); j < 3; j++) {
            c = row / 3 * 3 + (row + i) % 9 % 3;
            d = col / 3 * 3 + (col + j) % 9 % 3;
            if (table[c][d] == a) {
                return true;
            }
        }
    }

    return false;

}

//In the marks 2-D array, search the row of the specified cell for a specified vaoue
//The 4th parameter works as follows:
//If remove = false => stop at the first instance of finding the value a and return the bool
//If remove = true => remove all instances of the value a in the row
bool searchMarksRow(int a, int row, int col, bool remove = false) {

    int c, d;
    for (int i = 1; i < 9; i++) {
        c = row;
        d = (col + i) % 9;
        if (find(marks[c][d].begin(), marks[c][d].end(), a) != marks[c][d].end()) {
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
bool searchMarksCol(int a, int row, int col, bool remove = false) {

    int c, d;
    for (int i = 1; i < 9; i++) {
        c = (row + i) % 9;
        d = col;
        if (find(marks[c][d].begin(), marks[c][d].end(), a) != marks[c][d].end()) {
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
        for (int j = (i == 0 ? 1 : 0); j < 3; j++) {
            c = row / 3 * 3 + (row + i) % 9 % 3;
            d = col / 3 * 3 + (col + j) % 9 % 3;
            if (find(marks[c][d].begin(), marks[c][d].end(), a) != marks[c][d].end()) {
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