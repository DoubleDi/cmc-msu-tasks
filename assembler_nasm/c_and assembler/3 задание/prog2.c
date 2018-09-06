#include <stdlib.h>
#include <stdio.h>
int a, b;

int mul(void)
{
        return a * b;
}
int add(void)
{
        return a + b;
}
int sub(void)
{
        return a - b;
}
int divid(void)
{
        return a / b;
}

int main(void)
{
    char c;
    int d;

 //   int (*mas[6])() = {mul, add, 0, sub, 0,  divid};
    int (*mas[6])(void);
    mas[0] = mul;
    mas[1] = add;
    mas[2] = 0;
    mas[3] = sub;
    mas[4] = 0;
    mas[5] = divid;
    scanf("%d%c%d", &a, &c, &b);
    c-=42;
    d = c;
    printf("%d", (*mas[d])());
    return 0;
}
