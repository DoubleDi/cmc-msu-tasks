#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *a, *x, n, i, k, m, t, sum;
    scanf("%d", &n);
    a = malloc(n * sizeof(int));
    for(i = 0; i < n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    x = malloc(m * sizeof(int));
    for(i = 0; i < m; i++) scanf("%d", &x[i]);
    for(i = m-1; i >= 0; i--)
    {
        t = 1;
        sum = 0;
        for(k = 0; k < n; k++)
        {
            sum += t*a[k];
            t *= x[i];
        }
    printf("%d ",sum);
    }
    return 0;
}
