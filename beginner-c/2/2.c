#include <stdio.h>

int main(void)
{
    int mas[10000], num, i = 0;
    scanf("%d", &mas[i]);
    while (mas[i])
    {
       if (!(i%2)) printf("%d ",mas[i]);
       i++;
       scanf("%d", &mas[i]);
    }
    if (i % 2) i -= 2;
    else i--;
    for(num = i; num >= 1 ; num -= 2) printf("%d ",mas[num]);
    return 0;
}
