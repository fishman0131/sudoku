#include <iostream>
#include <chrono>
#include <ratio>
#include "sudoku.h"

using namespace std;
int main()
{
    int i;
    cout << "please enter the sudoku" << endl;
    int a[9][9];
    for(i=0; i<9; i++)
            cin >> a[i][0] >> a[i][1] >> a[i][2]
                >> a[i][3] >> a[i][4] >> a[i][5]
                >> a[i][6] >> a[i][7] >> a[i][8];
    cout << endl;

    Sudoku sudoku(a);
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    sudoku.solve();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();  
    sudoku.print_result();

    chrono::steady_clock::duration delta = end - start;
    cout << "It took " << std::chrono::duration_cast<std::chrono::microseconds>(delta).count() 
         << " microseconds." << endl;

    return 0;
}
