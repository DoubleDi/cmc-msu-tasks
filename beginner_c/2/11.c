#include <stdio.h>

int main(void)
{
    int a[8][8], i, k, t = 0;
    for (i = 0; i < 8; i++)
        for (k = 0; k < 8; k++) a[i][k] = 0;
    while(((i = getchar()) != '\n') &&  (i != EOF))
    {
        i -= 'a';
        k = getchar() - '0' - 1;
        if (a[k][i] != 2)
        {
            a[k + 1 > 7 ? 7 : k + 1][i - 1 < 0 ? 1 : i - 1] = 1;
            a[k + 1 > 7 ? 7 : k + 1][i] = 1;
            a[k + 1 > 7 ? 7 : k + 1][i + 1 > 7 ? 7 : i + 1] = 1;
            a[k][i - 1 < 0 ? 1 : i - 1] = 1;
            a[k][i] = 2;
            a[k][i + 1 > 7 ? 7 : i + 1] = 1;
            a[k - 1 < 0 ? 1 : k - 1][i - 1 < 0 ? 1 : i - 1] = 1;
            a[k - 1 < 0 ? 1 : k - 1][i] = 1;
            a[k - 1 < 0 ? 1 : k - 1][i + 1 > 7 ? 7 : i + 1] = 1;
        }
    }
    for(i = 0; i < 8; i++)
        for(k = 0; k < 8; k++)  if (!a[i][k]) t++;
    printf("%d", t);
    return 0;
}
