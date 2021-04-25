#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;
class Sudoku 
{
    int sudoku[9][9]; //[row][col]
    int block[9][9];

    bool is_legal(int row, int col, int num)
    {
        int i, j;
        //row
        for(i = 0; i < 9; i++)
            if(sudoku[i][col] == num)
                return false;
        //col
        for(i = 0; i < 9; i++)
            if(sudoku[row][i] == num)
                return false;

        //sudoku
        for(i = (row/3)*3; i < (row/3+1)*3; i++)
            for(j = (col/3)*3; j < (col/3+1)*3; j++)
                if(sudoku[i][j] == num)
                    return false;
            
        return true;
    }

    bool set_num(int row, int col)
    {
        if(block[row][col] != 0) 
        {
            return true;
        }
        int num;
        for(num = sudoku[row][col]+1; num <=9; num++)
        {
            if(is_legal(row, col, num))
            {
                sudoku[row][col] = num;
                return true;
            }
        }
        return false;
    }

public:
    void solve()
    {
        int step=0, row, col;
        while(step < 81)
        {
            if(set_num(step/9, step%9))
            {
                step++;
            }
            else
            {
                sudoku[step/9][step%9] = 0;
                do
                {
                    if(step > 0)
                        step--;
                } while(block[step/9][step%9] != 0);
            }
        }
    }

    void print_result()
    {
        int i, j;
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                cout << sudoku[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    Sudoku(int in_soduko[9][9])
    {
        memset(sudoku, 0, sizeof(sudoku));
        memset(block, 0, sizeof(block));
        memcpy(sudoku, in_soduko, sizeof(sudoku));
        memcpy(block, in_soduko, sizeof(block));
    }
};