#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int calc(int a, int b, char op)
{
    if (op == '*') return a * b;
    else return a / b;
}


int work(char op)
{
    int num1, num2, i;
    char nextop, numstack[33] = "";
    getchar();
    nextop = getchar();
    if ((nextop == '*') || (nextop == '/')) num1 = work(nextop);
    else
    {
        numstack[0] = nextop;
        while ((nextop = getchar()) != ' ')
            numstack[strlen(numstack)] = nextop;
        num1 = atoi(numstack);
    }
    nextop = getchar();
    for(i = 0; i < 33; i++) numstack[i] = '\0';
    if ((nextop == '*') || (nextop == '/')) num2 = work(nextop);
    else
    {
        numstack[0] = nextop;
        while (((nextop = getchar()) != ' ') && (nextop != EOF) && (nextop != '\n'))
            numstack[strlen(numstack)] = nextop;
        num2 = atoi(numstack);
    }
    return calc(num1, num2, op);
}


int main(void)
{
    char op;
    op = getchar();
    printf("%d", work(op));
    return 0;
}
