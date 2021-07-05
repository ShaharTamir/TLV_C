#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen, strcpy */

#define N 4

typedef struct
{
    int row;
    int col;
} Cell;

/* question 2 */
void testWhat();
int what(char st[], char c);

/* question 4 */
void testPath();
char hasPath(int mat[][N], int n, Cell start, Cell end);
char IndexValid(Cell pos, int n);
int Pos(int mat[][N], Cell pos);

int main()
{
    /* testWhat(); */
    testPath();

    return 0;
}

/* Question 2 from test */
void testWhat()
{
    int result = 0;
    char lookFor = 'h';
    char str[] = "blah blah blah\0";

    result = what(str, lookFor);

    printf("result = %d, the new string is: \"%s\"", result, str);
}

void testPath()
{
    int mat[][N] = {{0, 1, 1, 0},
                    {1, 1, 0, 1},
                    {0, 1, 1, 1},
                    {0, 0, 0, 1}};

    Cell start = {0, 1};
    Cell end = {3, 3};
    printf("result success = %d\n", hasPath(mat, N, start, end));
    start.col = 0;
    printf("result failure = %d\n", hasPath(mat, N, start, end));
}

/*
*   remove all chars that are equal to c parameter from st,
*   count and return how many c characters removed from st.
*/
int what(char st[], char c)
{
    int i = 0;
    int j = 0;
    int cn = 0;
    int length = 0;
    char* st2;

    length = strlen(st);
    st2 = (char*) malloc(length);

    if(!st2)
    {
        printf("malloc failed.. shit\n");
        return 0;
    }

    /* copy to st2 without 'c' */
    while(st[i] != '\0')
    {
        if(st[i] != c)
        {
            st2[j] = st[i];
            ++j;
        }
        else
            ++cn;

        ++i;
    }

    st2[j] = '\0'; /* EOS */

    /* copy back to st */
    for(i = 0; i <= j; ++i)
    {
        st[i] = st2[i];
    }

    /* remove garbage */
    for(i; i < length; ++i)
    {
        st[i] = '\0';
    }

    free(st2);

    return cn;
}


char hasPath(int mat[][N], int n, Cell start, Cell end)
{
    char res = 0;
    /* validate */
    if(!IndexValid(start, n) || Pos(mat, start) != 1)
        return 0;
    /* success */
    if(start.row == end.row && start.col == end.col)
        return 1;

    mat[start.row][start.col] = 2;

    /* recursive call */
    /* right */
    start.col += 1;
    res |= hasPath(mat, n, start, end);
    /* left */
    start.col -= 2;
    res |= hasPath(mat, n, start, end);
    /* reset */
    start.col += 1;
    /* up */
    start.row -= 1;
    res |= hasPath(mat, n, start, end);
    /* down */
    start.row += 2;
    res |= hasPath(mat, n, start, end);
    /* reset */
    start.row -= 1;

    mat[start.row][start.col] = 1;

    /* result of recursive call */
    return res;
}

char IndexValid(Cell pos, int n)
{
    return pos.row >= 0 && pos.col >= 0 && pos.row < n && pos.col < n;
}

int Pos(int mat[][N], Cell pos)
{
    return mat[pos.row][pos.col];
}