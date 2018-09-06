#include <stdio.h>

int main(void)
{
    unsigned a,i,k,t = 0;
    scanf("%u%u",&a,&k);
    for (i = 0; i < k; i++)
    {
        t = t | 1;
        t <<= 1;
    }
    t >>= 1;
    printf("%u",a & t);

    return 0;
}
