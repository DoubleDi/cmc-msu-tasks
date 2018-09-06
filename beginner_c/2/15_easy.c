#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned long n, *mas, *mas1 ,* mas0, t1 = 0, t2 = 0, i = 0, k = 0, j = 0;
    scanf("%lu", &n);
    mas = malloc(n * sizeof(unsigned long));
    mas1 = malloc(n * sizeof(unsigned long));
    mas0 = malloc(n * sizeof(unsigned long));
    for(i = 0; i< n; i++)
    {
        scanf("%lu", &mas[i]);
        t1 ^= mas[i];
    }
    for(i = 0; i < n; i++)
        if ((mas[i] ^ t1) > mas[i])
        {
            mas1[k] = mas[i];
            k++;
        }
        else
        {
            mas0[j] = mas[i];
            j++;
        }
        t1 = 0;
    for(i = 0; i < k; i++) t1 ^= mas1[i];
    for(i = 0; i < j; i++) t2 ^= mas0[i];
    printf("%lu %lu", t1 > t2 ? t2 : t1, t1 > t2 ? t1 : t2);

}
