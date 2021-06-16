#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#define TRUE 1
#define FALSE 0
#define LIM 31

/* API functions */
int Weights(int ar[], int size, int target);
void All_Weights(int ar[], int size, int target);

/* Service functions*/
int Recursive_Weights(int ar[], int check[], int size, int target, int curr_index, int sum, int print);
void Print_Weights(int ar[], int check[], int size);

int main()
{
    int arr[] = {2, 5, 1, 4, 6, 9};
    int tgt = 0;

    for(tgt = 0; tgt < LIM; ++tgt)
    {
        printf("target %d:\t%s\n", tgt, TRUE == Weights(arr, sizeof(arr) / sizeof(int), tgt) ? "true" : "false");
        All_Weights(arr, sizeof(arr) / sizeof(int), tgt);
    }

    return 0;
}

int Weights(int ar[], int size, int target)
{
    return Recursive_Weights(ar, NULL, size, target, 0, 0, FALSE);
}

void All_Weights(int ar[], int size, int target)
{
    int *check = NULL;
    int i = 0;
    int j = 0;

    check = (int *) malloc(size * sizeof(int));
    if(!check)
    {
        printf("malloc failed! exit All_Weights.\n");
        return;
    }

    for(i = 0; i < size; ++i)
    {
        for(j = 0; j < size; ++j) /* reset check */
        {
            check[j] = 0;
        }
        
        Recursive_Weights(&ar[i], &check[i], size - i, target, 0, 0, TRUE);
    }

    free(check);
    check = NULL;
}

int Recursive_Weights(int ar[], int check[], int size, int target, int curr_index, int sum, int print)
{
    int res = FALSE;

    if(curr_index >= size || curr_index < 0)
        return FALSE;
    
    if(print)
        check[curr_index] = 1;

    if(sum + ar[curr_index] == target)
    {
        if(print && check[0] == 1) /* print weight sets by order of weights */
        {
            Print_Weights(ar, check, size);
        }

        return TRUE;
    }
    
    /* use |= so that if found at least one TRUE res will return TRUE */
    res |= Recursive_Weights(ar, check, size, target, curr_index + 1, sum + ar[curr_index], print); /* check adding curr index to sum */
    
    if(print)
        check[curr_index] = 0;
    
    res |= Recursive_Weights(ar, check, size, target, curr_index + 1, sum, print); /* check without adding curr index to sum */

    return res;
}

void Print_Weights(int ar[], int check[], int size)
{
    int count = 0;
    int i = 0;

    for(i = 0; i < size; ++i)
    {
        if(check[i])
            ++count;
    }

    for(i = 0; i < size; ++i)
    {
        if(check[i])
        {
            if(count > 1)
                printf("%d, ", ar[i]);
            else /* last */
                printf("%d\n", ar[i]);
            --count;
        }
    }   
}