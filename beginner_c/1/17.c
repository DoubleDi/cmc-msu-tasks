#include <stdio.h>

int main(void)
{
    unsigned long long n,x = 0,i,k;
    scanf("%llu",&n);
    for (i = 0;i < n;i++)
    {
        scanf("%llu",&k);
        x = x ^ k;
    }
    printf("%llu", x);
    return 0;
}
