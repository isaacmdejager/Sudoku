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

}