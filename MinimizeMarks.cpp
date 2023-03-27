#include <iostream>
#include <vector>
#include "TableGenerator.h"
#include "Search.h"
#include "TableSolver.h"
#include "ConfirmValue.h"

using namespace std;

bool removeMark(int a, int row, int col) {

    int index = -1;
    for (int i = 0; i < marks[row][col].size(); i++) {
        if (marks[row][col][i] == a) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        marks[row][col].erase(marks[row][col].begin() + index);
        return true;
    }

    return false;
    
}

//EXCLUSION

//Given a cell, if that cell is solved then remove its mark from all rows, columns, and blocks
bool exclusion(int row, int col) {

    bool markRemoved = false;

    if (marks[row][col].size() == 1) {

        int a = marks[row][col][0];
        if (searchMarksRow(a, row, col, true)) {
            markRemoved = true;
        }

        if (searchMarksCol(a, row, col, true)) {
            markRemoved = true;
        }

        if (searchMarksBlock(a, row, col, true)) {
            markRemoved = true;
        }

    }

    

    return markRemoved;

} 


//INTERSECTION

//Suppose a given cell C has a mark X. If, for all cells in the same row BUT NOT the same column,
//X is not a mark, then remove X from the 6 cells in the same block as C but not the same row
bool BlockRowIntersection(int row, int col) {

    bool markRemoved = false;
    for (int i = 0; i < marks[row][col].size(); i++) {
        if (
            marks[row][col].size() > 1 &&
            !searchRowMinusBlock(marks[row][col][i], row, col) &&
            searchBlockMinusRow(marks[row][col][i], row, col, true)
        ) {
            markRemoved = true;
        }
    }

    return markRemoved;

}

//Given a cell C with mark X, if for all cells in the same column but not the same block, X is not
//a mark, then remove X from the 6 cells in the same block as C but not the same column
bool BlockColIntersection(int row, int col) {

    bool markRemoved = false;
    for (int i = 0; i < marks[row][col].size(); i++) {
        if (
            marks[row][col].size() > 1 && 
            !searchColMinusBlock(marks[row][col][i], row, col) &&
            searchBlockMinusCol(marks[row][col][i], row, col, true)
        ) {
            markRemoved = true;
        }
    }

    return markRemoved;

}

//Given a cell C with mark X, if for all cells in the same block but not the same row, X is not
//a mark, then remove X from the 6 cells in the same row as C but not the same block
bool RowBlockIntersection(int row, int col) {

    bool markRemoved = false;
    for (int i = 0; i < marks[row][col].size(); i++) {
        if (
            marks[row][col].size() > 1 &&
            !searchBlockMinusRow(marks[row][col][i], row, col) &&
            searchRowMinusBlock(marks[row][col][i], row, col, true)
        ) {
            markRemoved = true;
        }
    }

    return markRemoved;

}

//Given a cell C with mark X, if for all cells in the same block but no the same column, X is not
//a mark, then remove X from the 6 cells in the same row as C but no the same block
bool ColBlockIntersection(int row, int col) {

    bool markRemoved = false;
    for (int i = 0; i < marks[row][col].size(); i++) {
        if (
            marks[row][col].size() > 1 &&
            !searchBlockMinusCol(marks[row][col][i], row, col) &&
            searchColMinusBlock(marks[row][col][i], row, col, true)
        ) {
            markRemoved = true;
        }
    }

    return markRemoved;

}

bool intersection(int row, int col) {

    bool markRemoved = false;

    if (BlockRowIntersection(row, col)) {
        markRemoved = true;
    }
    
    if (BlockColIntersection(row, col)) {
        markRemoved = true;
    }
    
    if (RowBlockIntersection(row, col)) {
        markRemoved = true;
    }
        
    if (ColBlockIntersection(row, col)) {
        markRemoved = true;
    }

    return false;

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

bool FindNakedSubset(int n, vector<int> perm) {

    vector<int> m;
    vector<int> cells = inversePermutation(perm);
    int c, d;
    bool markRemoved = false;

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
                        markRemoved = removeMark(m[p], c, d);
                    }

                }

            }

        }

    }

    return markRemoved;

}

// n = size of subset
// index = current index of subset
// arr = full subset
bool permutation(int n, int index, vector<int> arr) {

    bool markRemoved = false;
    for (int i = index == 0 ? 0 : arr[index - 1] + 1; i < 10 - n + index; i++) {
        
        arr[index] = i;
        if (index != n - 1) {
            if (permutation(n, index + 1, arr)) {
                markRemoved = true;
            }
        } else {
            //At every permutation, find the union of marks amongst the row, column and block
            if (FindNakedSubset(n, arr)) {
                markRemoved = true;
            }
        }

    }

    return markRemoved;

}

bool NakedSubset() {

    vector<int> arr;
    arr.push_back(0);
    bool markRemoved = false;

    //Create all permutations of [0 - 8], starting with tuple size 2 up to size 8
    for (int i = 2; i < 9; i++) {
        arr.push_back(0);
        if (permutation(i, 0, arr)) {
            markRemoved = true;
        }
    }

    return markRemoved;

}


//X-WING
//Consider a 4 cells inside that table that create a rectangle (the 4 cells are the corners).
//If all 4 cells share the same mark X, and X appears in no other cells in the rows of the cells
//Then X can be removed from all other cells in the same column
//The inverse it true for columns and rows

//Search either the given row or column to see if there are at least 3 instaces of the same
//mark

bool checkForThree(int v, int i, bool row) {

    int counter = 0;
    for (int j = 0; j < 9; j++) {
        if (row ? searchMarks(v, i, j) : searchMarks(v, j, i)) {
            counter++;
            if (counter > 2) {
                return true;
            }
        }
    }

    return false;

}

//Upon finding an X-Wing, remove the value from either the rows or columns
bool cutWings(int v, int block[4], int row) {

    bool markRemoved = false;
    for (int i = 0; i < 9; i++) {
        if (row == 0 && i != block[0] && i != block[2]) {
            if (removeMark(v, i, block[1])) {
                markRemoved = true;
            }
            if (removeMark(v, i, block[3])) {
                markRemoved = true;
            }
        }
        else if (row == 1 && i != block[1] && i != block[3]) {
            if (removeMark(v, block[0], i)) {
                markRemoved = true;
            }
            if (removeMark(v, block[2], i)) {
                markRemoved = true;
            }
        }
    }

    return markRemoved;

}

bool createXWing(int v, int i, int block[4], int row) {

    bool markRemoved = false;
    for (int j = (i < 2 ? i / 2 : block[i % 2] + 1); j < 8 + i / 2; j++) {

        if (i % 2 == row && checkForThree(v, j, i % 2 == 0)) {
            continue;
        }

        block[i] = j;
        if (i < 3) {
            createXWing(v, i + 1, block, row);
        } 
        else if (
                searchMarks(v, block[0], block[1]) && 
                searchMarks(v, block[0], block[3]) &&
                searchMarks(v, block[2], block[1]) &&
                searchMarks(v, block[2], block[3])
            ) {
            if (cutWings(v, block, row)) {
                markRemoved = true;
            }
        }

    }    

    return markRemoved;

}

bool XWing() {

    int block[4];
    bool markRemoved = false;

    for (int i = 1; i < 10; i++) {

        //Row
        if (createXWing(i, 0, block, 0)) {
            markRemoved = true;
        }
        
        //Column
        if (createXWing(i, 0, block, 1)) {
            markRemoved = true;
        }

    }
    
    return markRemoved;

}


// Run through all MinimizeMarks methods, cut down as many marks as possible
bool cutMarks() {

    bool markRemoved = false;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (exclusion(i, j)) {
                markRemoved = true;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (intersection(i, j)) {
                markRemoved = true;
            }
        }
    }
   
    if (NakedSubset()) {
       markRemoved = true;
    }

    if (XWing()) {
       markRemoved = true;
    }

    return markRemoved;
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



// bool Nishio() {

//     vector<int> snapShot[9][9];
//     vector<int> unsolvedCells;
//     int a, b;

//     //Take a snapshot of the marks and find all unsolved cells
//     for (int i = 0; i < 81; i++) {

//         a = i / 9;
//         b = i % 9;
//         for (int j = 0; j < marks[a][b].size(); j++) {
//             snapShot[a][b].push_back(marks[a][b][j]);
//         }

//         if (marks[a][b].size() > 1) {
//             unsolvedCells.push_back(i);
//         }

//     }

//     // Select a random unsovled cell and loop through its marks
//     if (unsolvedCells.size() == 0) {
//         cout << "oh boy" << endl;
//     }
//     int r = rand() % unsolvedCells.size();
//     a = unsolvedCells[r] / 9;
//     b = unsolvedCells[r] % 9;

//     int c, d;

//     for (int i = 0; i < snapShot[a][b].size(); i++) {

//         setValue(snapShot[a][b][i], a, b);
//         if (solveTable()) {
//             return true;
//         }

//         for (int j = 0; j < 81; j++) {
//             c = j / 9;
//             d = j % 9;
//             marks[c][d].clear();
//             for (int k = 0; k < snapShot[c][d].size(); k++) {
//                 marks[c][d].push_back(snapShot[c][d][k]);
//             }
//         }

//     }

//     return false;

// }