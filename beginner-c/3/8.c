#include <stdio.h>
#include <stdlib.h>

long med(long a, long b, long c)
{
    return (a > b) ? ((b > c) ? b : ((a > c) ? c : a)) : ((a > c) ? a : ((b > c) ? c : b));
}

int main(void)
{
    int n, i, k;

    long *mas;
    scanf("%d", &n);
    mas = malloc(n * sizeof(long));
    for(i = 0; i < n; i++)
        scanf("%ld", &mas[i]);
    for(i = n; i > 1; i-=2)
        for(k = 1; k < i - 1; k++)
            mas[k-1] = med(mas[k - 1], mas[k], mas[k + 1]);
    printf("%ld", mas[0]);
    free(mas);
}
