#include <stdio.h>

int n, k, mas[14], t = -1;

void lexi(int last, int kol)
{
    int i;
    t++;
    if (kol == k)
    {
        for (i = 0; i < k; i++) printf("%d ",mas[i]);
        printf("\n");
    }
    else
        for (i = last + 1; i < n; i++)
        {
            mas[kol] = i;
            lexi(i,kol + 1);
        }
}

int main(void)
{

    scanf("%d%d", &n, &k);
    lexi(-1, 0);// последнее число и количество
    return 0;
}
