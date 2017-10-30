#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int k, i, j, n, m, *a, *b, *c;
    scanf("%d", &n);
    a = malloc(n * sizeof(int));
    for(i = 0; i < n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    b = malloc(m * sizeof(int));
    for(j = 0; j < m; j++) scanf("%d", &b[j]);
    c = malloc((m+n) * sizeof(int));
    i = 0;
    j = 0;
    k = 0;
    while ((i < n) || (j < m))
    {
        if (i < n)
        {
            c[k] = a[i];
            i++;
            k++;
        }
        if (j < m)
        {
            c[k] = b[j];
            j++;
            k++;
        }
    }
    for(i = 0; i < k; i++) printf("%d ",c[i]);
    free(a);
    free(b);
    free(c);
    return 0;
}
