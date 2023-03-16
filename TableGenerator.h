#include <vector>

using namespace std;

extern int table[9][9];
extern vector<int> marks[9][9];

void generate();
void removeMark(int a, int row, int col);

void printTable();
void printMarks();