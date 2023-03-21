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

    for (int i = 0; i < 19; i++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < 9; i++) {

        cout << "|";
        for (int j = 0; j < 9; j++) {
            
            if (j % 3 != 0) {
                cout << " ";
            }
            if (table[i][j] != 0) {
                cout << table[i][j];
            } else {
                cout << " ";
            }

            if (j % 3 == 2) {
                cout << "|";
            }
        }
        cout << endl;
        if (i % 3 == 2) {
            for (int j = 0; j < 19; j++) {
                cout << "-";
            }
            cout << endl;
        }

    }

}

void printMarks() {

    for (int i = 0; i < 57; i++) {
        cout << "-";
    }
    cout << endl;



    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 3; j++) {

            cout << "|";
            for (int p = 0; p < 9; p++) {
                
                for (int k = 0; k < 3; k++) {

                    if (searchMarks(3 * j + k + 1, i, p)) {
                        cout << 3 * j + k + 1;
                    } else {
                        cout << " ";
                    }

                    if (k < 2) {
                        cout << " ";
                    } else {
                        if (p % 3 == 2 && p != 8) {
                            cout << "||";
                        } else {
                            cout << "|";
                        }
                        
                    }

                }

            }
            cout << endl;

        }


        if(i != 8) {
            for (int j = 0; j < 18; j++) {
            cout << "-";
        }
        cout << "||";
        for (int j = 0; j < 17; j++) {
            cout << "-";
        }
        cout << "||";
        for (int j = 0; j < 18; j++) {
            cout << "-";
        }
        cout << endl;
        }


        if (i % 3 == 2) {
            if(i != 8) {
            for (int j = 0; j < 18; j++) {
            cout << "-";
        }
        cout << "||";
        for (int j = 0; j < 17; j++) {
            cout << "-";
        }
        cout << "||";
        for (int j = 0; j < 18; j++) {
            cout << "-";
        }
        cout << endl;
        }
        }

        


    }




    for (int i = 0; i < 57; i++) {
        cout << "-";
    }
    cout << endl;

    

    

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