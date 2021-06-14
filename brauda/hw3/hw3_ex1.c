#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */

#define NUM_BALLS 30
#define NUM_COLORS 3

/* requested functions */
void place_balls_to_array(int* arr, int size);
void print_array(int* arr, int size);
void sort_balls(int* arr, int size);

/* service functions */
void swap_integers(int* a, int* b);

int main(void)
{
    int arr[NUM_BALLS];

    place_balls_to_array(arr, NUM_BALLS);
    printf("before sorting:\n");
    print_array(arr, NUM_BALLS);

    sort_balls(arr, NUM_BALLS);
    printf("after sorting:\n");
    print_array(arr, NUM_BALLS);

    return 0;
}

void place_balls_to_array(int* arr, int size)
{
    int i = 0;

    for(i = 0; i < size; ++i)
    {
        arr[i] = rand() % NUM_COLORS; /* fill array with random values between 0 - 2 */
    }
}

void print_array(int* arr, int size)
{
    /* match index of letter to value of red, yellow and green */
    const char colors[] = {'R', 'Y', 'G'};
    int i = 0;

    for(i = 0; i < size; ++i)
    {
        printf("%c,", colors[arr[i]]); /* print the letter according to arr[i] index val */
    }

    printf("\n");
}

void sort_balls(int* arr, int size)
{
    int i = 0;
    int j = 0;

    /* bubble sort down - bubble lower values left */
    for(i = 1; i < size; ++i)
    {
        j = i;
        while(j - 1 >= 0 && arr[j - 1] > arr[j])
        {
            swap_integers(&arr[j - 1], &arr[j]);
            --j;
        }
    }
}

void swap_integers(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
