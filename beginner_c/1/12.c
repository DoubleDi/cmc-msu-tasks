#include <stdio.h>

void swap(long long *x, long long *y)
{
    long long z = *x;
    *x = *y;
    *y = z;
}

int main(void)
{
    long long a,b,c,n,k,i;
    scanf("%lld",&n);
    scanf("%lld%lld%lld",&a,&b,&c);
    if (a < c) swap(&a,&c);
    if (a < b) swap(&a,&b);
    if (b < c) swap(&b,&c);
    for (i = 0;i < n - 3;i++)
    {
        scanf("%lld",&k);
        if (k > a)
        {
            c = b;
            b = a;
            a = k;
        }
        else if ((k == a) || (k > b))
        {
            c = b;
            b = k;
        }
        else if (((k == a) && (k == b)) || (k > c)) c = k;
    }
    printf("%lld %lld %lld\n",a,b,c);
    return 0;
}
