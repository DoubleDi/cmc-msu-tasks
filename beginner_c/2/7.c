#include <stdio.h>

int main(void)
{
    int x, i, n,  a[10001], p = 0;
    for(i = 1; i < 10001; i++) a[i] = 0;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &x);
        if (x <= 0) p = 1;
        else a[x]++;
    }

    x = 0;
    if (!p)
        for(i = 1; i < 10001; i++)
        {
            if (a[i] > 1)
            {
                p = 1;
                break;
            }
            else if ((x) && (a[i] >= 1))
            {
                p = 1;
                break;
            }
            else if (a[i] == 0) x = 1;
        }
    if (!p) printf("Yes");
    else printf("No");
    return 0;
}
