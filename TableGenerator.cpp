#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

//Initialize Sudoku table and the table pencil marks
int table[9][9];
vector<int> marks[9][9];

void printTable() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }

}

void printMarks() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << "[ ";
            for (int k = 0; k  < marks[i][j].size(); k++) {
                cout << marks[i][j][k] << " ";
            }
            cout << "]";
        }
        cout << endl;
    }

}

void assignRandomValue(int row, int col) {

    int r = rand() % marks[row][col].size();
    table[row][col] = marks[row][col][r];
    

    marks[row][col].clear();
    marks[row][col].push_back(table[row][col]);

}


void removeMark(int a, int row, int col) {

    remove(marks[row][col].begin(), marks[row][col].end(), a);

}

bool searchTableRow(int a, int row, int col) {

    for (int i = 1; i < 9; i++) {
        if (table[row][(col + i) % 9] == a) {
            return true;;
        }
    }

    return false;

}

bool searchMarksRow(int a, int row, int col, bool remove) {

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

bool searchTableCol(int a, int row, int col) {

    for (int i = 1; i < 9; i++) {
        if (table[(row + i) % 9][col] == a) {
            return true;
        }
    }

    return false;

}

bool searchMarksCol(int a, int row, int col, bool remove) {

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

bool searchMarksBlock(int a, int row, int col, bool remove) {

    int c, d;

    for (int i = 0; i < 3; i++) {
        for (int j = (i == 0 ? 1 : 0); j < 3; j++) {
            c = row / 3 * 3 + (row + i) % 9 % 3;
            d = col / 3 * 3 + (row + i) % 9 % 3;
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

//As soon as a value in the table is set, exclusion removes that value from
//all marks in the same row, column, and block all the newly set cell
void exclusion(int row, int col) {

    int a = table[row][col];

    //remove a from all marks in the same row
    searchMarksRow(a, row, col, true);

    //remove a from all marks in the same column
    searchMarksCol(a, row, col, true);

    //remove a from all marks in the same block
    searchMarksBlock(a, row, col, true);

}

int main() {

    //Initialize Sudoku table and the table pencil marks
    // for (int i = 0; i < 81; i++) {
    //     table[i / 9][i % 9] = i;
    // }

    // searchTableRow(1, 1, 1, &printNo);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            table[i][j] = 0;
            for (int k = 1; k < 10; k++) {
                marks[i][j].push_back(k);
            }
        }
    }

    srand(time(0));
    
    //Randomly select n cells, make sure they are unique
    //n must be less than 9. For once n is greater than or
    //equal to 9, it is possible to randomly generate an
    //unsolvable board
    vector<int> initCells;
    int r, n = 8;
    for (int i = 0; i < n; i++) {
        r = 1 + (rand() % 81);

        if (find(initCells.begin(), initCells.end(), r) == initCells.end()) {
            initCells.push_back(r);
        } else {
            i--;
        }
    }

    //In these n cells, randomly assign them values
    int c, d;
    for (int i = 0; i < n; i++) {
        c = initCells[i] / 9;
        d = initCells[i] % 9;
        assignRandomValue(c, d);
        exclusion(c, d);
    }

    printTable();
    printMarks();
    
    
}