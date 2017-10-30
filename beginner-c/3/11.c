#include <stdio.h>

int nod(int a, int b)
{
    if ((a == 0) || (b == 0)) return a + b;
    else return nod(b % a, a);
}

void sum (int *x, int *y, int *z)
{
    int a, b, t;
    scanf("%d%d", &a, &b);
    *y = (*y) * b + a * (*z);
    *z = (*z) * b;

    t = nod(*z, *y);
    *z /= t;
    *y /= t;
    if (*y >= *z)
    {
        *x += *y / *z;
        *y %= *z;
    }
}

int main(void)
{
    int i, x = 0, y = 0, z = 1, n;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        sum(&x, &y, &z);
    printf("%d %d %d", x, y, z);
    return 0;
}
