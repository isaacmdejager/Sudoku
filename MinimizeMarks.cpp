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


void printVector(vector<int> vect) {

    cout << "[";
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i];
        if (i != vect.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

}

vector<int> inversePermutation(vector<int> perm) {

    vector<int> p;

    for (int i = 0; i < 9; i++) {
        if (find(perm.begin(), perm.end(), i) == perm.end()) {
            p.push_back(i);
        }
    }

    return p;

}

vector<int> unionMarks(vector<int> perm, string sector, int n) {

    vector<int> m, cell;

    for (int i = 0; i < perm.size(); i++) {

        //ROW
        if (sector == "row") {
            cell = marks[n][perm[i]];
        }

        //COLUMN
        else if (sector == "column") {
            cell = marks[perm[i]][n];
        }

        //BLOCK
        else {
            cell = marks[3 * (n / 3) + perm[i] / 3][3 * (n % 3) + perm[i] % 3];
        }

        for (int j = 0; j < cell.size(); j++) {
            if (find(m.begin(), m.end(), cell[j]) == m.end()) {
                m.push_back(cell[j]);
            }
        }
        
    }

    return m;

}

void FindNakedSubset(int n, vector<int> perm) {

    //With the given permutation, we apply that permutation to every row,
    //column and block in the table

    vector<int> m;
    vector<int> cells = inversePermutation(perm);


    for (int i = 0; i < 3; i++) {
        
    }




    //ROW
    for (int r = 0; r < 9; r++) {

        m = unionMarks(perm, "row", r);
        if (m.size() == n) {

            //Loop through all cells in the given row/col/block that are not in the permutation
            for (int i = 0; i < cells.size(); i++) {
                //Loop through the union of marks and remove those values from the cells not in
                //the permutation
                for (int j = 0; j < m.size(); j++) {
                    removeMark(m[j], r, cells[i]);
                }
            }

        }

    }

    //COLUMN
    for (int c = 0; c < 9; c++) {

        m = unionMarks(perm, "column", c);
        if (m.size() == n) {

            for (int i = 0; i < cells.size(); i++) {
                for (int j = 0; j < m.size(); j++) {
                    removeMark(m[j], cells[i], c);
                }
            }

        }

    }

    //BLOCK
    for (int b = 0; b < 9; b++) {

        m = unionMarks(perm, "block", b);
        if (m.size() == n) {

            for (int i = 0; i < cells.size(); i++) {
                for (int j = 0; j < m.size(); j++) {
                    removeMark(m[j], 3 * (b / 3) + cells[i] / 3, 3 * (b % 3) + cells[i] % 3);
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
