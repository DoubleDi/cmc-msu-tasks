#include <stdio.h>

long nod(long a, long b)
{
    if ((a == 0) || (b == 0)) return a + b;
    else return nod (b % a, a);
}


int main(void)
{
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    printf("%ld", nod(a, nod(b, nod(c, d))));
    return 0;
}
