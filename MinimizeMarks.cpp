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

//INTERSECTION

//Suppose a given cell C has a mark X. If, for all cells in the same row BUT NOT the same column,
//X is not a mark, then remove X from the 6 cells in the same block as C but not the same row
void BlockRowIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchRowMinusBlock(marks[row][col][i], row, col)) {
            searchBlockMinusRow(marks[row][col][i], row, col, true);
        }
    }

}

//Given a cell C with mark X, if for all cells in the same column but not the same block, X is not
//a mark, then remove X from the 6 cells in the same block as C but not the same column
void BlockColIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchColMinusBlock(marks[row][col][i], row, col)) {
            searchBlockMinusCol(marks[row][col][i], row, col, true);
        }
    }

}

//Given a cell C with mark X, if for all cells in the same block but not the same row, X is not
//a mark, then remove X from the 6 cells in the same row as C but not the same block
void RowBlockIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchBlockMinusRow(marks[row][col][i], row, col)) {
            searchRowMinusBlock(marks[row][col][i], row, col, true);
        }
    }

}

//Given a cell C with mark X, if for all cells in the same block but no the same column, X is not
//a mark, then remove X from the 6 cells in the same row as C but no the same block
void ColBlockIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchBlockMinusCol(marks[row][col][i], row, col)) {
            searchColMinusBlock(marks[row][col][i], row, col, true);
        }
    }

}