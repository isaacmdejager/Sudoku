#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

//Initialize Sudoku table and the table pencil marks
int table[9][9];
vector<int> marks[9][9];

void printVector(vector<int> vect) {
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << endl;
}

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

//Checks the status of the sudoku table and returns whether or not the board is fully filled
bool filled() {

    int a;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] == 0) {
                return false;
            }
        }
    }

    return  true;
}

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

bool searchTableRow(int a, int row, int col) {

    for (int i = 1; i < 9; i++) {
        if (table[row][(col + i) % 9] == a) {
            return true;;
        }
    }

    return false;

}

//Search the row of a given cell for a value. The 4th parameter is added for mark removals
//If remove = true and a is found, then remove that value and continue. If remove = false and a is
//found, the function immediately returns true
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

//Search the column of a given cell for a value. The 4th parameter is added for mark removals
//If remove = true and a is found, then remove that value and continue. If remove = false and a is
//found, the function immediately returns true
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

//Search the block of a given cell for a value. The 4th parameter is added for mark removals
//If remove = true and a is found, then remove that value and continue. If remove = false and a is
//found, the function immediately returns true
bool searchMarksBlock(int a, int row, int col, bool remove) {

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

void exclusion(int a, int row, int col) {

    //remove a from all marks in the same row
    searchMarksRow(a, row, col, true);

    //remove a from all marks in the same column
    searchMarksCol(a, row, col, true);

    //remove a from all marks in the same block
    searchMarksBlock(a, row, col, true);

}

void setValue(int a, int row, int col) {
    
    table[row][col] = a;
    marks[row][col].clear();
    marks[row][col].push_back(a);

    //After setting a value, remove marks from all cells that you can
    exclusion(a, row, col);
    
}

bool singleCandidate(int row, int col) {

    if (marks[row][col].size() == 1) {
        setValue(marks[row][col][0], row, col);
        return true;
    }
    return false;

}

//If a mark only appears in one cell of a given row, col or block, that mark must be set
//in that cell
bool eliminationCandidate(int row, int col) {

    int a;
    for (int i = 0; i < marks[row][col].size(); i++) {

        a = marks[row][col][i];
        if (
            !searchMarksRow(a, row, col, false) ||
            !searchMarksCol(a, row, col, false) ||
            !searchMarksBlock(a, row, col, false)
        ) {
            setValue(a, row, col);
            return true;
        }

    }

    return false;

}

void assignRandomValue(int row, int col) {

    int r = rand() % marks[row][col].size();
    setValue(marks[row][col][r], row, col);

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
        r = rand() % 80;

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
    }

    //Now, we continuously loop through the table. For every entry, we check to see
    //if we can either fill a value, or use the marks at that entry to remove marks
    //in other scenarios

    // //This loops infinetly and will only break when the
    // for (int i = 0; i < 81; i = (i + 1) % 81) {

    // }


    int reset = 0;
    //Keep this loop cycled while there are still entries to be filled in the sudoku table
    do {

        //Loop through every cell
        //If you reach a cell where something is changed, reset the loop
        //If you reach the end of the loop (go through everything with no changes)
        //Then you know that the board is either solved or unsolvable
        for (int i = 0; i < 81; i++) {

            c = (i + reset) % 81 / 9;
            d = (i + reset) % 9;

            if (
                table[c][d] == 0 &&
                (singleCandidate(c, d) ||
                eliminationCandidate(c, d))
            ) {
                reset = (i + 1) % 81;
                i = -1;
            }

        }

        printTable();

    } while (!filled());
    
    
}