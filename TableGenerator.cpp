#include <iostream>
#include <vector>
#include "TableGenerator.h"
#include "Search.h"
#include "ConfirmValue.h"
#include "MinimizeMarks.h"

using namespace std;

int table[9][9] = { { 0 } };
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
            cout << "[";
            for (int k = 0; k < marks[i][j].size(); k++) {
                cout << marks[i][j][k] << " ";
            }
            cout << "]";
        }
        cout << endl;
    }

}

void generate() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for(int k = 1; k < 10; k++) {
                marks[i][j].push_back(k);
            }
        }
    }


    // marks[0][0].erase(marks[0][0].begin() + 4);
    // marks[0][1].erase(marks[0][1].begin() + 4);
    // marks[0][5].erase(marks[0][5].begin() + 4);

    for (int i = 0; i < 7; i++) {
        marks[3][4].erase(marks[3][4].begin());
        marks[5][3].erase(marks[5][3].begin());
        marks[5][8].erase(marks[5][8].begin());
        marks[1][4].erase(marks[1][4].begin());
    }

    // marks[0][4].clear();
    // marks[0][4].push_back(5);


    // for (int i = 0; i < 7; i++) {
    //     marks[4][0].erase(marks[4][0].begin());
    //     marks[4][2].erase(marks[4][2].begin());
    //     marks[4][6].erase(marks[4][6].begin() + 8 - i);
    //     marks[4][8].erase(marks[4][8].begin() + 8 - i);
    // }

    // marks[4][4].clear();
    // marks[4][4].push_back(5);


    printMarks();
    cout << "-----------" << endl;

    NakedSubset();

    printMarks();

}