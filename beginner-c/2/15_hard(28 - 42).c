#include <stdio.h>
#include <stdlib.h>

void work(unsigned long mas1[], unsigned long i, unsigned long mas0[], unsigned long k, unsigned long xr)
{
    unsigned long *mas11, *mas10, *mas01, *mas00, j, i11 = 0, i10 = 0, k00 = 0, k01 = 0;
    static unsigned long indicate = 1;
    if ((k != 0) && (i != 0))
    {
        if (i == 1)
        {
            for(j = 0; j < k; j++)
                if ((mas1[0] ^ mas0[j]) == xr) printf("%lu %lu", mas1[0] > mas0[j] ? mas0[j] : mas1[0], mas1[0] < mas0[j] ? mas0[j] : mas1[0]);
        }
        else  if (k == 1)
        {
            for(j = 0; j < i; j++)
                if ((mas1[j] ^ mas0[0]) == xr) printf("%lu %lu", mas1[j] > mas0[0] ? mas0[0] : mas1[j], mas1[j] < mas0[0] ? mas0[0] : mas1[j]);
        }
        else
        {
            indicate <<= 1;
            mas11 = malloc(i * sizeof(unsigned long));
            mas10 = malloc(i * sizeof(unsigned long));
            mas01 = malloc(k * sizeof(unsigned long));
            mas00 = malloc(k * sizeof(unsigned long));
            for (j = 0; j < i; j++)
                if (mas1[j] & indicate)
                {
                    mas11[i11] = mas1[j];
                    i11 ++;
                }
            else
                {
                    mas10[i10] = mas1[j];
                    i10 ++;
                }
            for (j = 0; j < k; j++)
                if (mas0[j] & indicate)
                {
                    mas01[k01] = mas0[j];
                    k01 ++;
                }
                else
                {
                    mas00[k00] = mas0[j];
                    k00 ++;
                }
            if (i % 2)
            {
                if ((i11 % 2) && (k01 % 2)) work(mas11, i11, mas01, k01, xr);
                if ((i11 % 2) && (k00 % 2)) work(mas11, i11, mas00, k00, xr);
                if ((i10 % 2) && (k01 % 2)) work(mas10, i10, mas01, k01, xr);
                if ((i10 % 2) && (k00 % 2)) work(mas10, i10, mas00, k00, xr);
            }
            else
            {
                if ((i11 % 2) && (i10 % 2)) work(mas11, i11, mas10, i10, xr);
                if ((k00 % 2) && (k01 % 2)) work(mas00, k00, mas01, k01, xr);
                if ((!(i11 % 2)) && (!(i10 % 2))) work(mas11, i11, mas10, i10, xr);
                if ((!(k00 % 2)) && (!(k01 % 2))) work(mas00, k00, mas01, k01, xr);
            }
        }
    }
}

int main(void)
{
    unsigned long n, xr = 0, *mas1 ,* mas0, t = 0 ,i = 0, k = 0;
    scanf("%lu", &n);
    mas1 = malloc(n * sizeof(unsigned long));
    mas0 = malloc(n * sizeof(unsigned long));
    while (i + k < n)
    {
        scanf("%lu", &t);
        xr ^= t;
        if (t & 1)
        {
            mas1[i] = t;
            i++;
        }
        else
        {
            mas0[k] = t;
            k++;
        }
    }
    if (n == 1) printf("%lu", t);
    work(mas1, i, mas0, k, xr);
    return 0;
}
