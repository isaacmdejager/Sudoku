#include "TableGenerator.h"
#include "Search.h"

using namespace std;

void removeMark(int a, int row, int col) {

    int index;
    for (int i = 0; i < marks[row][col].size(); i++) {
        if (marks[row][col][i] == a) {
            index = i;
            break;
        }
    }
    marks[row][col].erase(marks[row][col].begin() + index);

}

//Given a value and a cell, remove the value from all marks in the same row, column,
//and block as the given cell
void exclusion(int a, int row, int col) {

    searchMarksRow(a, row, col, true);
    searchMarksCol(a, row, col, true);
    searchMarksBlock(a, row, col, true);

}