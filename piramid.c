#include <stdio.h>


void main(void)
{
    int number;

    printf("please enter number to piramid: ");
    scanf("%d", &number);

    for(int i = 1; i <= number; ++i)
    {
        int count = 1;

        for(; count < i; ++count)
        {
            printf("%d", count);
        }

        while(count)
        {
            printf("%d", count);
            --count;
        }

        printf("\n");
    }


}
