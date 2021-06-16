#include <stdio.h>  /* printf, scanf */
#include <stdlib.h> /* malloc, free, srand, rand */
#include <time.h>   /* to init srand */

#define MIN_SIZE 3
#define MAX_SIZE 20
#define MANUAL_INPUT 0
#define HOR  0
#define DIAG 1

/* API functions */
int** Gen_Matrix(int size, int digits);
int** Gen_Matrix_From_User(int size);
int** Find_Course(int *ar[], int size, int diag_hor);
int Recurse_Find_Course(int **ar, int **course, int size, int diag_hor, int row, int col, int compare_num, int starting_row);
void Print_Matrix(int *ar[], int *res_ar[], int size);

/* Service functions */
void Handle_Menu(int *size, int *mode);
void Free_Matrix(int *ar[], int size);
int Index_Valid(int r, int c, int size);
void Print_Regular_Mat(int **mat, int size);
void Check_Course(int **generated_mat, int matrix_size, int diag_hor, char *name);

int main()
{
    int **generated_mat = NULL;
    int matrix_size = 0;
    int user_option = -1;

    Handle_Menu(&matrix_size, &user_option);
    
    if(MANUAL_INPUT == user_option)
        generated_mat = Gen_Matrix_From_User(matrix_size);
    else /* generate random matrix */
    {
        srand(time(NULL));
        generated_mat = Gen_Matrix(matrix_size, user_option);
    }

    if(NULL == generated_mat)
        return 1; /* no memory, a message is printed in Gen_Matrix */
    
    Print_Regular_Mat(generated_mat, matrix_size);
    Check_Course(generated_mat, matrix_size, DIAG, "diagonal");
    Check_Course(generated_mat, matrix_size, HOR, "horizontal");

    Free_Matrix(generated_mat, matrix_size);
    generated_mat = NULL;

    return 0;
}

int** Gen_Matrix(int size, int digits)
{
    int **gen_mat = NULL;
    int r = 0;
    int c = 0;

    gen_mat = (int**) malloc(size * sizeof(int*));
    
    if(NULL != gen_mat)
    {
        for(r = 0; r < size; ++r)
        {
            gen_mat[r] = (int*) malloc(size * sizeof(int));
            if(NULL != gen_mat[r])
            {
                for(c = 0; c < size; ++c)
                {
                    if(0 == digits)     /* generate mat from user */
                        scanf("%d", &gen_mat[r][c]); 
                    else if(digits > 0) /* generate mat for user */
                        gen_mat[r][c] = (rand() % digits) + 1;
                    else                /* create a mat filled with 0 */
                        gen_mat[r][c] = 0;
                }
            }
            else
                Free_Matrix(gen_mat, r);
        }
    }
    else
        printf("malloc failed. exit.\n");

    return gen_mat;
}

int** Gen_Matrix_From_User(int size)
{
    return Gen_Matrix(size, 0);
}

int** Find_Course(int *ar[], int size, int diag_hor)
{
    int **res_mat = NULL;
    int res = 0;
    res_mat = Gen_Matrix(size, -1); /* generate a matrix filled with 0's */

    if(NULL != res_mat)
    {        
        res = Recurse_Find_Course(ar, res_mat, size, diag_hor, 0, 0, ar[0][0], 0); /* start from up-left corner */
        if(0 == res) /* didn't find a course */
        {
            Free_Matrix(res_mat, size);
            res_mat = NULL;
        }
    }

    return res_mat;
}

int Recurse_Find_Course(int **ar, int **course, int size, int diag_hor, int row, int col, int compare_num, int starting_row)
{
    if(Index_Valid(row, col, size) && compare_num == ar[row][col] && !course[row][col])
    { /* index valid && this cell equals the cell from the start of  course && didn't check this cell yet */
        course[row][col] = 1; /* mark as checked */

        if(size - 1 == col && /* reached other side of mat */
            (HOR == diag_hor || /* horizontal is always valid, diagonal check valid. */
            (DIAG == diag_hor && ((0 == starting_row && size - 1 == row) || (size - 1 == starting_row && 0 == row))))) 
        {   
            return 1;   /* found a path */
        }

        if(Recurse_Find_Course(ar, course, size, diag_hor, row, col + 1, compare_num, starting_row) ||  /* right */
            Recurse_Find_Course(ar, course, size, diag_hor, row + 1, col, compare_num, starting_row) || /* down */
            Recurse_Find_Course(ar, course, size, diag_hor, row - 1, col, compare_num, starting_row) || /* up */
            Recurse_Find_Course(ar, course, size, diag_hor, row, col - 1, compare_num, starting_row))   /* left */
        {
            return 1;
        }

        course[row][col] = 0; /* didn't find a path, fold back and delete the current course */

        if(DIAG == diag_hor && 0 == starting_row && 0 == row && 0 == col)
            /* didn't find a diaognal course on the up-left corner. check from down-left corner */ 
            return Recurse_Find_Course(ar, course, size, diag_hor, size - 1, 0, ar[size - 1][0], size - 1);

        else if(HOR == diag_hor && 0 == col && row == starting_row && row + 1 < size)
            /* didn't find a course in this row. check next. */
            return Recurse_Find_Course(ar, course, size, diag_hor, row + 1, 0, ar[row + 1][0], row + 1);
    }

    return 0;
}

void Print_Matrix(int *ar[], int *res_ar[], int size)
{
    int r = 0;
    int c = 0;

    printf("\n");
    for(r = 0; r < size; ++r)
    {
        for(c = 0; c < size; ++c)
        {
            if(res_ar[r][c])
                printf("*%d*\t", ar[r][c]);
            else
                printf("%d\t", ar[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void Handle_Menu(int *size, int *mode)
{
    printf("Enter size of matrix (3 - 20): ");
    scanf("%d", size);

    while(*size < MIN_SIZE || *size > MAX_SIZE)
    {
        printf("size is not valid, enter another: ");
        scanf("%d", size);
    }

    printf("Enter 0 - Manual input\nn - random positive digits\n");
    scanf("%d", mode);
}

void Free_Matrix(int **ar, int size)
{
    int r = 0;

    for(r = 0; r < size; ++r)
    {
        free(ar[r]);
        ar[r] = NULL;
    }

    free(ar);
    ar = NULL;
}

int Index_Valid(int r, int c, int size)
{
    if(r < 0 || r >= size || c < 0 || c >= size)
        return 0;
    
    return 1;
}

void Print_Regular_Mat(int **mat, int size)
{
    int i = 0;
    int j = 0;

    printf("starting matrix:\n\n");
    for(i = 0; i < size; ++i)
    {
        for(j = 0; j < size; ++j)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Handle output to user, run Find_Course, handle memory managment */
void Check_Course(int **generated_mat, int matrix_size, int diag_hor, char *name)
{
    int **res_mat = NULL;

    printf("check for %s course\n", name);
    res_mat = Find_Course(generated_mat, matrix_size, DIAG);

    if(NULL == res_mat)
        printf("diagonal course not found\n");
    else
    {
        Print_Matrix(generated_mat, res_mat, matrix_size);
        Free_Matrix(res_mat, matrix_size);
        res_mat = NULL;
    }
}