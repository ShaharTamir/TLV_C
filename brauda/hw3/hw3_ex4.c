#include <stdio.h> /* printf */

#define MATRIX_SIZE 9
#define ROW_FACTOR 3

/* requested functions */
void solve_sudoku(int board[MATRIX_SIZE][MATRIX_SIZE]);
void print_sudoku(int board[MATRIX_SIZE][MATRIX_SIZE]);

/* service functions */
int exist_in_col(int board[MATRIX_SIZE][MATRIX_SIZE], int col, int num);

int main()
{
    int board[MATRIX_SIZE][MATRIX_SIZE] = {0};

    solve_sudoku(board);
    print_sudoku(board);

    return 0;
}

void solve_sudoku(int board[MATRIX_SIZE][MATRIX_SIZE])
{
    int row, col;
    int num = 1;

    for(row = 0; row < MATRIX_SIZE; ++row)
    {
        if(exist_in_col(board, 0, num))
            num = num + 1 > MATRIX_SIZE ? 1 : num + 1;
        
        for(col = 0; col < MATRIX_SIZE; ++col)
        {
            board[row][col] = num;

            num = num + 1 > MATRIX_SIZE ? 1 : num + 1;
        }

        num -= ROW_FACTOR; /* factor deducted from the picture in the instructions doc */
        num = num > 0 ? num : MATRIX_SIZE + num; /* + num because num is negative */
    }
}

void print_sudoku(int board[MATRIX_SIZE][MATRIX_SIZE])
{
    int row, col;

    printf("\n");
    for(row = 0; row < MATRIX_SIZE; ++row)
    {
        for(col = 0; col < MATRIX_SIZE; ++col)
        {
            printf(" %d", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

int exist_in_col(int board[MATRIX_SIZE][MATRIX_SIZE], int col, int num)
{
    int row;

    for(row = 0; row < MATRIX_SIZE; ++row)
    {
        if(board[row][col] == num)
            return 1;
    }

    return 0;
}