#include <stdio.h>

int main(void)
{
    long s = 0,a,b = 0,i=0;
    scanf("%ld",&a);
    s += a;
    if (a) scanf("%ld",&a);
    while (a)
    {
        i++;
        if (!(i % 2)) s += b * a;
        b = a;
        scanf("%ld",&a);
    }
    if (i % 2) s += b;
    printf("%ld",s);
    return 0;
}
