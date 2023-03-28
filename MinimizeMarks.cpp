#include <iostream>
#include <vector>
#include "TableGenerator.h"
#include "Search.h"
#include "TableSolver.h"

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

//Given a cell, if that cell is solved then remove its mark from all rows, columns, and blocks
void exclusion(int row, int col) {

    if (marks[row][col].size() == 1) {
        
        int a = marks[row][col][0];
        searchMarksRow(a, row, col, true);
        searchMarksCol(a, row, col, true);
        searchMarksBlock(a, row, col, true);

    }

} 


//INTERSECTION

//Suppose a given cell C has a mark X. If, for the 6 cells in the same row but not the same block as C,
//X is not a mark, then remove X from the 6 cells in the same block as C but not the same row
void BlockRowIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchRowMinusBlock(marks[row][col][i], row, col)) {
            searchBlockMinusRow(marks[row][col][i], row, col, true);
        }
    }

}

//Suppose a given cell C has a mark X. If, for the 6 cells in the same column but not he same block as C, 
//X is not a mark, then remove X from the 6 cells in the same block as C but not the same column
void BlockColIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchColMinusBlock(marks[row][col][i], row, col)) {
            searchBlockMinusCol(marks[row][col][i], row, col, true);
        }
    }

}

//Suppose a given cell C has a mark X. If, for the 6 cells in the same block but not same row as C,
//X is not a mark, then remove X from the 6 cells in the same row as C but not the same block
void RowBlockIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchBlockMinusRow(marks[row][col][i], row, col)) {
            searchRowMinusBlock(marks[row][col][i], row, col, true);
        }
    }

}

//Suppose a given cell C has mark X. If, for the 6 cells in the same block but not the same column as C,
//X is not a mark, then remove X from the 6 cells in the same column as C but not the same block
void ColBlockIntersection(int row, int col) {

    for (int i = 0; i < marks[row][col].size(); i++) {
        if (!searchBlockMinusCol(marks[row][col][i], row, col)) {
            searchColMinusBlock(marks[row][col][i], row, col, true);
        }
    }

}

void intersection(int row, int col) {

    if (marks[row][col].size() > 1) {

        BlockRowIntersection(row, col);
        BlockColIntersection(row, col);
        RowBlockIntersection(row, col);
        ColBlockIntersection(row, col);

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
            //At every permutation, find the union of marks amongst the row, column and block
            FindNakedSubset(n, arr);
        }

    }

}

void NakedSubset() {

    vector<int> arr;
    arr.push_back(0);

    //Create all permutations of [0 - 8], starting with tuple size 2 up to size 8
    for (int i = 2; i < 9; i++) {
        arr.push_back(0);
        permutation(i, 0, arr);
    }

}


//X-WING
//Consider a 4 cells inside that table that create a rectangle (the 4 cells are the corners).
//If all 4 cells share the same mark X, and X appears in no other cells in the rows of the cells
//Then X can be removed from all other cells in the same column
//The inverse it true for columns and rows

//Search either the given row or column to see if there are at least 3 instaces of the same
//mark

bool checkForThree(int v, int i, bool isRow) {

    int counter = 0;
    for (int j = 0; j < 9; j++) {
        if (isRow ? searchMarks(v, i, j) : searchMarks(v, j, i)) {
            counter++;
            if (counter > 2) {
                return true;
            }
        }
    }

    return false;

}

//Upon finding an X-Wing, remove the value from either the rows or columns
void cutWings(int v, int corners[4], int isRow) {

    for (int i = 0; i < 9; i++) {
        if (isRow == 0 && i != corners[0] && i != corners[2]) {
            removeMark(v, i, corners[1]);
            removeMark(v, i, corners[3]);
        }
        else if (isRow == 1 && i != corners[1] && i != corners[3]) {
            removeMark(v, corners[0], i);
            removeMark(v, corners[2], i);
        }
    }

}

void createXWing(int v, int i, int corners[4], int isRow) {

    for (int j = (i < 2 ? i / 2 : corners[i % 2] + 1); j < 8 + i / 2; j++) {

        if (i % 2 == isRow && checkForThree(v, j, i % 2 == 0)) {
            continue;
        }

        corners[i] = j;
        if (i < 3) {
            createXWing(v, i + 1, corners, isRow);
        } 
        else if (
                searchMarks(v, corners[0], corners[1]) && 
                searchMarks(v, corners[0], corners[3]) &&
                searchMarks(v, corners[2], corners[1]) &&
                searchMarks(v, corners[2], corners[3])
            ) {
            cutWings(v, corners, isRow);
        }

    }    

}

void XWing() {

    int corners[4];

    for (int i = 1; i < 10; i++) {

        //Row
        createXWing(i, 0, corners, 0);

        //Column
        createXWing(i, 0, corners, 1);

    }

}


// Run through all MinimizeMarks methods, cut down as many marks as possible
void cutMarks() {

    bool markRemoved = false;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            exclusion(i, j);
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            intersection(i, j);
        }
    }
   
    NakedSubset();

    XWing();

}

bool Nishio() {

    vector<int> snapShot[9][9];
    vector<int> unsolvedCells;
    int a, b;

    for (int i = 0; i < 81; i++) {

        a = i / 9;
        b = i % 9;
        for (int j = 0; j < marks[a][b].size(); j++) {
            snapShot[a][b].push_back(marks[a][b][j]);
        }

        if (marks[a][b].size() > 1) {
            unsolvedCells.push_back(i);
        }

    }

    int r = rand() % unsolvedCells.size();
    a = unsolvedCells[r] / 9;
    b = unsolvedCells[r] % 9;

    int c, d;
    for (int i = 0; i < snapShot[a][b].size(); i++) {


        marks[a][b].clear();
        marks[a][b].push_back(snapShot[a][b][i]);

        if (solveTable()) {
            return true;
        }

        for (int j = 0; j < 81; j++) {
            
            c = j / 9;
            d = j % 9;
            marks[c][d].clear();
            for (int k = 0; k < snapShot[c][d].size(); k++) {
                marks[c][d].push_back(snapShot[c][d][k]);
            }
        }

    }

    return false;

}