#include <stdio.h>

typedef enum
{
    FALSE,
    TRUE
} bool;

int sumEvenOdd(unsigned int num);
double power(double x, unsigned int n);
void separateEvenOdd(int num, int *even, int *odd);
int countScoreOptions(int score);
void printSubSeq(char str[], char let);
bool isPrefix(char str1[], char str2[]);
void combineArray(int sortedArr1[], int size1, int sortedArr2[], int size2);
int countSmaller(int arr[], int start, int end, int num);

void testSum();
void testPow();
void testEvenOdd();
void testCountScoreOp();
void testSubSeq();
void testPrefix();
void testCombine();
void testSmaller();

int main()
{
    /*testSum();*/
    /*testPow();*/
    /*testEvenOdd();*/
    /*testCountScoreOp();*/
    /*testSubSeq();*/
    /*testPrefix();*/
    /*testCombine();*/
    testSmaller();

    return 0;
}

int sumEvenOdd(unsigned int num)
{
    int sum;

    if(0 == num)
        return 0;

    sum = sumEvenOdd(num / 10);
    
    if((num % 10) % 2 == 0)
        return sum + (num % 10);       
    
    return sum - (num % 10);
}

double power(double x, unsigned int n)
{
    if(!n)
        return 1;

    return x * power(x, n - 1);
}

void separateEvenOdd(int num, int *even, int *odd)
{
    if(!num)
    {
        *even = *odd = 0;
        return;
    }

    separateEvenOdd(num / 10, even, odd);

    if((num % 10) % 2 == 0)
        *even = *even * 10 + (num % 10);
    else
        *odd = *odd * 10 + (num % 10);
}

int countScoreOptions(int score)
{
    if(0 == score)
        return 1;
    if(score < 0)
        return 0;

    return countScoreOptions(score - 1) + countScoreOptions(score - 2) + countScoreOptions(score - 3);
}

void printSubSeq(char str[], char let)
{
    if(*str == '\0')
        return;

    printSubSeq(str + 1, let);

    if(*str == let)
        printf("%s\n", str);
}

bool isPrefix(char str1[], char str2[])
{
    if(*str2 == '\0')
        return TRUE;

    if(*str1 == '\0')
        return FALSE;

    if(*str1 == *str2)
        return isPrefix(++str1, ++str2);
}

void combineArray(int sortedArr1[], int size1, int sortedArr2[], int size2)
{
    if(size1 == 0)
        return;
    
    if(size2 == 0)
    {
        *sortedArr2 = *sortedArr1;
        combineArray(++sortedArr1, --size1, sortedArr2, ++size2);

        return;
    }

    if(*sortedArr1 < *sortedArr2)
    {
        int tmp = *sortedArr2;
        *sortedArr2 = *sortedArr1;
        *sortedArr1 = tmp;
    }
    
    combineArray(sortedArr1, size1, ++sortedArr2, --size2);
}

int countSmaller(int arr[], int start, int end, int num)
{
    if(start >= end || arr[start] >= num)
        return 0;

    return 1 + countSmaller(arr, start + 1, end, num);
}

void testSum()
{
    int a = 2345672;
    int b = 1235124;
    int c = 11111;
    int d = 22222;

    int aExp = -1;
    int bExp = -2;
    int cExp = -5;
    int dExp = 10;

    printf("a: %d\n", sumEvenOdd(a) == aExp);
    printf("b: %d\n", sumEvenOdd(b) == bExp);
    printf("c: %d\n", sumEvenOdd(c) == cExp);
    printf("d: %d\n", sumEvenOdd(d) == dExp);
}

void testPow()
{
    double a = 4;
    unsigned int an = 2;
    double b = -6.5;
    unsigned int bn = 9;
    double c = 10;
    unsigned int cn = 10;
    double d = 3.14;
    unsigned int dn = 0;
    
    double aExp = 16;
    double bExp = -20711912.837890625;
    double cExp = 10000000000;
    double dExp = 1;

    printf("a: %d\n", power(a, an) == aExp);
    printf("b: %d\n", power(b, bn) == bExp);
    printf("c: %d\n", power(c, cn) == cExp);
    printf("d: %d\n", power(d, dn) == dExp);
}

void testEvenOdd()
{
    int a = 2345672;
    int b = 1235124;
    int c = 11111;
    int d = 22222;

    int aEvRes, aOddRes, bEvRes, bOddRes, 
        cEvRes, cOddRes, dEvRes, dOddRes;

    int aEvenExp = 2462;
    int aOddExp = 357;
    int bEvenExp = 224;
    int bOddExp = 1351;
    int cEvenExp = 0;
    int cOddExp = 11111;
    int dEvenExp = 22222;
    int dOddExp = 0;

    separateEvenOdd(a, &aEvRes, &aOddRes);
    separateEvenOdd(b, &bEvRes, &bOddRes);
    separateEvenOdd(c, &cEvRes, &cOddRes);
    separateEvenOdd(d, &dEvRes, &dOddRes);

    printf("a: %d\n", aEvenExp == aEvRes && aOddExp == aOddRes);
    printf("b: %d\n", bEvenExp == bEvRes && bOddExp == bOddRes);
    printf("c: %d\n", cEvenExp == cEvRes && cOddExp == cOddRes);
    printf("d: %d\n", dEvenExp == dEvRes && dOddExp == dOddRes);
}

void testCountScoreOp()
{
    int a = 3;
    int b = -3;
    int c = 4;
    int d = 6;

    int aExp = 4;
    int bExp = 0;
    int cExp = 7;
    int dExp = 24;

    printf("a: %d\n", countScoreOptions(a) == aExp);
    printf("b: %d\n", countScoreOptions(b) == bExp);
    printf("c: %d\n", countScoreOptions(c) == cExp);
    printf("d: %d\n", countScoreOptions(d) == dExp);
}

void testSubSeq()
{
    char str[] = "Hello World!\0";
    char let1 = 'l';
    char let2 = 'o';
    char let3 = 's';
    char let4 = 'H';

    printSubSeq(str, let1);
    printSubSeq(str, let2);
    printSubSeq(str, let3);
    printSubSeq(str, let4);
}

void testPrefix()
{
    printf("%d\n", isPrefix("", ""));
    printf("%d\n", isPrefix("Daniel is ", ""));
    printf("%d\n", isPrefix("Daniel", "Dan"));
    printf("%d\n", isPrefix("Dan", "Daniel"));
}

void testCombine()
{
    int Arr1[] = {-3, 1, 5};
    int Arr2[] = {-7, -1, -1, 1, 6, 0, 0, 0};

    combineArray(Arr1, 3, Arr2, 5);

    for(int i = 0; i < sizeof(Arr2) / sizeof(int); ++i)
    {
        printf("%d, ", Arr2[i]);
    }
    printf("\n");
}

void testSmaller()
{
    int arr[] = {-6, -4, 0, 1, 4, 6, 10, 100};
    int a = -7;
    int b = -3;
    int c = 7;
    int d = 101;

    int expA = 0;
    int expB = 2;
    int expC = 6;
    int expD = 8;
    int expC1 = 0;
    int expC2 = 4;

    printf("a: %d\n", countSmaller(arr, 0, 8, a) == expA);
    printf("b: %d\n", countSmaller(arr, 0, 8, b) == expB);
    printf("c: %d\n", countSmaller(arr, 0, 8, c) == expC);
    printf("d: %d\n", countSmaller(arr, 0, 8, d) == expD);
    printf("c1: %d\n", countSmaller(arr, 6, 8, c) == expC1);
    printf("c2: %d\n", countSmaller(arr, 2, 6, c) == expC2);
}