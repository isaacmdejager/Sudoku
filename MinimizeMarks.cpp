#include <iostream>
#include <vector>
#include "TableGenerator.h"
#include "Search.h"

using namespace std;

void removeMark(int a, int row, int col) {

    int index = -1;
    for (int i = 0; i < marks[row][col].size(); i++) {
        if (marks[row][col][i] == a) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        marks[row][col].erase(marks[row][col].begin() + index);
    }
    
}

//EXCLUSION

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


//NAKED SUBSET
//Consider a row R with subset |S| = n. If the union of all marks in S has cardinality n
//then all marks in S can be removed from all other cells in R.
//The same holds true for all columns and blocks.

vector<int> inversePermutation(vector<int> perm) {

    vector<int> p;

    for (int i = 0; i < 9; i++) {
        if (find(perm.begin(), perm.end(), i) == perm.end()) {
            p.push_back(i);
        }
    }

    return p;

}

vector<int> unionMarks(vector<int> perm, int sector, int n) {

    vector<int> m, cell;

    for (int i = 0; i < perm.size(); i++) {

        //ROW
        if (sector == 0) {
            cell = marks[n][perm[i]];
        }

        //COLUMN
        else if (sector == 1) {
            cell = marks[perm[i]][n];
        }

        //BLOCK
        else {
            cell = marks[3 * (n / 3) + perm[i] / 3][3 * (n % 3) + perm[i] % 3];
        }

        //Search the cell for its marks. If it reaches a mark that has not been added to the union, add it
        for (int j = 0; j < cell.size(); j++) {
            if (find(m.begin(), m.end(), cell[j]) == m.end()) {
                m.push_back(cell[j]);
            }
        }
        
    }

    return m;

}

void FindNakedSubset(int n, vector<int> perm) {

    vector<int> m;
    vector<int> cells = inversePermutation(perm);
    int c, d;

    //Rows, Columns, and Blocks
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 9; j++) {

            //Find the union of marks in the given cells, calculated via permutation
            m = unionMarks(perm, i, j);

            //If the length of the permutation equals the cardinaility of the union of marks, then
            //we remove the union of marks from all cells in the row/column/block not in the permutation
            if (m.size() == n) {

                for (int k = 0; k < cells.size(); k++) {

                    //Row
                    if (i == 0) {
                        c = j;
                        d = cells[k];
                    }

                    //Column
                    else if (i == 1) {
                        c = cells[k];
                        d = j;
                    }

                    //Block
                    else {
                        c = 3 * (j / 3) + cells[k] / 3;
                        d = 3 * (j % 3) + cells[k] % 3;
                    }

                    //For all values in the union of marks, remove them from cells not in the permutation
                    for (int p = 0; p < m.size(); p++) {
                        removeMark(m[p], c, d);
                    }

                }

            }

        }

    }

}

// n = size of subset
// index = current index of subset
// arr = full subset
void permutation(int n, int index, vector<int> arr) {

    for (int i = index == 0 ? 0 : arr[index - 1] + 1; i < 10 - n + index; i++) {
        
        arr[index] = i;
        if (index != n - 1) {
            permutation(n, index + 1, arr);
        } else {
            
            //At every permutation, find the common mark set amongst the row, column and block
            FindNakedSubset(n, arr);

        }

    }

}

void NakedSubset() {

    vector<int> arr;
    arr.push_back(0);

    //Create all permutations of [0, 8], starting with tuple size 2 up to size 8
    for (int i = 2; i < 9; i++) {
        arr.push_back(0);
        permutation(i, 0, arr);
    }

}
