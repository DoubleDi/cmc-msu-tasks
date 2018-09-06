#include <stdio.h>

int max = -1, n, mas[14];

void work(int left, int right, int i)
{
    if (i > n - 1)
    {
        if (left == right)
            max = right > max ? right : max;
    }
    else
    {
        work(left + mas[i], right, i + 1);
        work(left, right + mas[i], i + 1);
        work(left, right, i + 1);
    }
}

int main(void)
{
    int i;
    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%d", &mas[i]);
    work(0, 0, 0);
    printf("%d", max);
    return 0;
}
