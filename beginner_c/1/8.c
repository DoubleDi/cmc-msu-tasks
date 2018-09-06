#include <stdio.h>
#include <math.h>

int main(void)
{
    unsigned max = 0,a,i,k,t = 0;
    scanf("%u%u",&a,&k);
    for (i = 0; i < k; i++)
    {
        t = t | 1;
        t <<= 1;
    }
    t >>= 1;
    if (a <= pow(2,k-1)) max = a;
    else for (i = 0;i < 32 ; i++)
    {
        printf("%u\n",a & t);
        max = max > (a & t) ? max : (a & t);
        a = (a >> 1) | (a << 31);
    }
    printf("%u",max);
    return 0;
}

