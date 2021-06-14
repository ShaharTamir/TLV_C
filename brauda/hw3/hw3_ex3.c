#include <stdio.h> /* printf */
#include <stdlib.h> /* rand */

#define M 17
#define NUM_NUMBERS_ALLOWED 2

/* requested functions */
void generate_picture(int arr[M][M]);
void print_picture(int arr[M][M]);
void mirror_picture(int arr[M][M]);

/* service function */
void swap_integers(int* a, int* b);

int main()
{
    int arr[M][M];

    printf("original image:\n");
    generate_picture(arr);
    print_picture(arr);

    printf("mirror image:\n");
    mirror_picture(arr);
    print_picture(arr);

    return 0;
}

void generate_picture(int arr[M][M])
{
    int row, col;
    
    for(row = 0; row < M; ++row)
    {
        for(col = 0; col < M; ++col)
        {
            arr[row][col] = rand() % NUM_NUMBERS_ALLOWED; /* generate values between 0 - 1 */
        }
    }
}

void print_picture(int arr[M][M])
{
    int row, col;
    
    printf("\n");
    for(row = 0; row < M; ++row)
    {
        for(col = 0; col < M; ++col)
        {
            printf("%d ", arr[row][col]);
        }
        
        printf("\n");
    }
    printf("\n");
}

void mirror_picture(int arr[M][M])
{
    int row, col_start, col_end;

    for(row = 0; row < M; ++row)
    {
        col_start = 0;
        col_end = M - 1; /* last column position */
        
        /* swap the values of each columns start and end, 
            while moving both indexes towrds the middle */
        while(col_start < col_end)
        {
            swap_integers(&arr[row][col_start], &arr[row][col_end]);
            ++col_start;
            --col_end;
        }
    }
}

void swap_integers(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
