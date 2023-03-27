#include <iostream>

#include "TableGenerator.h"
#include "Search.h"
#include "MinimizeMarks.h"

using namespace std;

void setValue(int a, int row, int col) {

    marks[row][col].clear();
    marks[row][col].push_back(a);

}