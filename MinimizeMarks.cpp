#include <iostream>
#include <vector>
#include "TableGenerator.h"
#include "Search.h"
#include "TableSolver.h"

using namespace std;

vector<int> removedMarks;

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
        if (find(removedMarks.begin(), removedMarks.end(), 9 * row + col) == removedMarks.end()) {
            removedMarks.push_back(9 * row  + col);
        }
        
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

    for (int i = 0; i < 8; i++) {
        if (find(perm.begin(), perm.end(), i) == perm.end()) {
            p.push_back(i);
        }
    }

    return p;

}

void printVector(vector<int> vect) {

    cout << "[";
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i];
        if (i < vect.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

}

vector<int> unionMarks(int cell, vector<int> cells) {

    vector<int> m;

    int row = cell / 9;
    int col = cell % 9;

    for (int i = 0; i < marks[row][col].size(); i++) {
        m.push_back(marks[row][col][i]);
    }

    for (int i = 0; i < cells.size(); i++) {

        row = cells[i] / 9;
        col = cells[i] % 9;

        for (int j = 0; j < marks[row][col].size(); j++) {
            if (find(m.begin(), m.end(), marks[row][col][j]) == m.end()) {
                m.push_back(marks[row][col][j]);
            }
        }

    }

    return m;
    
}

vector<int> getCells(int cell, int sector, vector<int> perm = vector<int>()) {

    vector<int> cells;
    int row, col;

    for (int i = 0; i < 8; i++) {

        if (sector == 0) {
            row = cell / 9;
            col = (cell % 9 + i + 1) % 9;
        }
        else if (sector == 1) {
            row = (cell / 9 + i + 1) % 9;
            col = cell % 9;
        }
        else {
            row = cell / 9 / 3 * 3 + ((cell % 9 % 3 + i + 1) / 3 + cell / 9 % 3) % 3;
            col = cell % 9 / 3 * 3 + (cell % 9 % 3 + i + 1) % 3;
        }

        if (perm.size() == 0) {
            if (marks[row][col].size() > 1) {
                cells.push_back(9 * row + col);
            }
        } else {
            if (find(perm.begin(), perm.end(), 9 * row + col) == perm.end()) {
                cells.push_back(9 * row + col);
            }
        }
        

    }

    return cells;

}

void removeInversePermMarks(vector<int> m, vector<int> inversePerm) {

    int row, col;

    for (int i = 0; i < inversePerm.size(); i++) {

        row = inversePerm[i] / 9;
        col = inversePerm[i] % 9;

        for (int j = 0; j < m.size(); j++) {

            removeMark(m[j], row, col);

        }

    }

}

void FindNakedSubset(int n, vector<int> perm, int cell, vector<int> potentialCells, int sector) {

    vector<int> cells, m;
    
    for(int i = 0; i < perm.size(); i++) {
        cells.push_back(potentialCells[perm[i]]);
    }

    m = unionMarks(cell, cells);

    if (m.size() == n) {

        vector<int> inversePerm = getCells(cell, sector, cells);
        removeInversePermMarks(m, inversePerm);

    }


}

void permutation(int n, int index, vector<int> perm, int cell, vector<int> potentialCells, int sector) {

    for (int i = index == 0 ? 0 : perm[index - 1] + 1; i < potentialCells.size() + 1 - n + index; i++) {
        
        perm[index] = i;
        if (index != n - 1) {
            permutation(n, index + 1, perm, cell, potentialCells, sector);
        } else {
            FindNakedSubset(n + 1, perm, cell, potentialCells, sector);
        }

    }

}

void NakedSubset(int cell) {

    int row = cell / 9;
    int col = cell % 9;
    vector<int> perm;
    vector<int> potentialCells;

    for (int i = 0; i < 3; i++) {

        potentialCells = getCells(cell, i);
        perm.clear();

        for (int j = 0; j < marks[row][col].size() - 2; j++) {
            perm.push_back(0);
        }

        for (int j = marks[row][col].size() - 1; j < potentialCells.size() + 1; j++) {
            perm.push_back(0);
            permutation(j, 0, perm, cell, potentialCells, i);
        }

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

float totalXWing = 0;
float x = 0;
float totalNS = 0;
float y = 0;

// Run through all MinimizeMarks methods, cut down as many marks as possible
void cutMarks() {

    do {

        removedMarks.clear();

        const clock_t exc = clock();

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                exclusion(i, j);
            }
        }

        // cout << "Exclusion = " << float(clock() - exc) << endl;

        const clock_t inter = clock();

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                intersection(i, j);
            }
        }

        // cout << "Intersection = " << float(clock() - inter) << endl;

        XWing();

        x++;
        // totalXWing += float(clock() - xw);

        // cout << "X-Wing = " << float(clock() - xw) << endl;

        // const clock_t ns = clock();


        //Loop the removed marks and apply NakedSubset
        //All cells that NakedSubset removes marks from will be pushed to the back
        const clock_t c = clock();

        for (int i = 0; i < removedMarks.size(); i++) {

            if (marks[removedMarks[i] / 9][removedMarks[i] % 9].size() > 1) {
                NakedSubset(removedMarks[i]);

                y++;
                // totalNS += float(clock() - ns);
            }

        }

        // if (removedMarks.size() > 0) {
        //     cout << "Naked Subset = " << float(clock() - ns) << endl;
        // }
        // cout << endl;


        // cout << totalXWing / x << endl;
        // cout << totalNS / y << endl;
        // cout << endl;


    } while (removedMarks.size() != 0);

}

bool Nishio() {

    vector<int> snapShot[9][9];
    vector<int> minMarkCells;
    int markCounts[81];
    int a, b, size, cell, r;
    int m = 10;

    for (int i = 0; i < 81; i++) {

        a = i / 9;
        b = i % 9;
        size = marks[a][b].size();
        for (int j = 0; j < size; j++) {
            snapShot[a][b].push_back(marks[a][b][j]);
        }

        markCounts[i] = size;
        if (size > 1 && size < m) {
            m = size;
        }

    }

    for (int i = 0; i < 81; i++) {

        if (markCounts[i] == m) {
            minMarkCells.push_back(i);
        }

    }

    size = minMarkCells.size();
    cell = minMarkCells[rand() % size];
    a = cell / 9;
    b = cell % 9;

    r = rand() % m;

    int c, d;
    for (int i = 0; i < m; i++) {


        marks[a][b].clear();
        marks[a][b].push_back(snapShot[a][b][(i + r) % m]);

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