#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LIM 31

/* API functions */
int Weights(int ar[], int size, int target);
int** All_Weights(int ar[], int size, int target);

/* Service functions*/
int Recursive_Weights(int ar[], int size, int target, int curr_index, int sum);

int main()
{
    int arr[] = {2, 5, 1, 4, 6, 9};

    for(int tgt = 0; tgt < LIM; ++tgt)
    {
        printf("target %d:\t%d\n", tgt, Weights(arr, sizeof(arr) / sizeof(int), tgt));
    }

    return 0;
}

int Weights(int ar[], int size, int target)
{
    return Recursive_Weights(ar, size, target, 0, 0);
}

int** All_Weights(int ar[], int size, int target)
{
    
}

int Recursive_Weights(int ar[], int size, int target, int curr_index, int sum)
{
    int res = FALSE;

    if(curr_index >= size || curr_index < 0)
        return FALSE;
    
    if(sum + ar[curr_index] == target)
        return TRUE;

    res = Recursive_Weights(ar, size, target, curr_index + 1, sum + ar[curr_index]); /* check adding curr index to sum */

    if(FALSE == res)
    {
        res = Recursive_Weights(ar, size, target, curr_index + 1, sum); /* check without adding curr index to sum */
    }

    return res;
}