#include <stdio.h>


int stepen(int a, int b, int m)
{
    int x = 1;
    while (b > 1)
        if (b % 2)
        {
            x = (x * a) % m;
            b--;
        }
        else
        {
            b /= 2;
            a = (a * a) % m;
        }
    return ((a * x) % m);
}


int main(void)
{
    int a, b, c, m, max = 0, X = 1000000000;
    scanf("%d%d%d%d", &a, &b, &c, &m);
    max = stepen(a % m, stepen(b % X, c, X), m) > max ? stepen(a % m, stepen(b % X, c, X), m) : max;
    max = stepen(a % m, stepen(c % X, b, X), m) > max ? stepen(a % m, stepen(c % X, b, X), m) : max;
    max = stepen(b % m, stepen(a % X, c, X), m) > max ? stepen(b % m, stepen(a % X, c, X), m) : max;
    max = stepen(b % m, stepen(c % X, a, X), m) > max ? stepen(b % m, stepen(c % X, a, X), m) : max;
    max = stepen(c % m, stepen(a % X, b, X), m) > max ? stepen(c % m, stepen(a % X, b, X), m) : max;
    max = stepen(c % m, stepen(b % X, a, X), m) > max ? stepen(c % m, stepen(b % X, a, X), m) : max;
    printf("%d", max);
    return 0;
}
