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
        //3*3 grid 
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

    /* A improvement which can cut the solving time spend in half,
       work like some grid can get the answer number through contrasting
       the number of row, col and 3*3 grid, and get more answer number 
       through recursive way.
    */
    bool pretreatment()
    {
        bool rc = true;
        int step;
        for(step = 0; step < 81; step++)
        {
            int row = step/9, col = step%9;
            if(block[row][col] != 0)
                continue;

            int i, j, bit_num = 0x3fe;
            //row
            for(i = 0; i < 9; i++)
                if(block[i][col] != 0)
                    bit_num &= ~(1<<block[i][col]);
            //col
            for(i = 0; i < 9; i++)
                if(block[row][i] != 0)
                    bit_num &= ~(1<<block[row][i]);
            //3*3 grid
            for(i = (row/3)*3; i < (row/3+1)*3; i++)
                for(j = (col/3)*3; j < (col/3+1)*3; j++)
                    if(block[i][j] != 0)
                        bit_num &= ~(1<<block[i][j]);

            for(i = 1; i <= 9; i++)
            {
                if((bit_num & (1<<i)) == bit_num)
                {
                    block[row][col] = i;
                    sudoku[row][col] = i;
                    if(rc)
                        rc = false;
                    break;
                }
            }
        }

        if(!rc) 
            return pretreatment();
        else
            return rc;
    }

public:
    bool solve()
    {
        pretreatment();

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
                    step--;
                    if(step < 0)
                    {
                        cout << "This sudoku is unsolvable" << endl;
                        return false;
                    }
                } while(block[step/9][step%9] != 0);
            }
        }
        
        return true;
    }

    void print_block()
    {
        int i, j;
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                cout << block[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
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
        memcpy(sudoku, in_soduko, sizeof(sudoku));
        memcpy(block, in_soduko, sizeof(block));
    }
};