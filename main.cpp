#include <iostream>
#include "TableGenerator.h"
#include "TableSolver.h"
#include "MinimizeMarks.h"

using namespace std;

int main() {

    generate();


    fillTable();

    printTable();


    // printMarks();
    // cout << endl;
    // cout << "=======================" << endl;
    // cout << endl;
    solveTable();




}