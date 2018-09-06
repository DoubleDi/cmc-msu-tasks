#include <stdio.h>

int main(void)
{
    long long a = 0,b = 0,c = 0,d = 0,n,i,x;
    scanf("%lld",&n);
    for (i = 0; i < n; i++)
    {
        scanf("%lld",&x);
        if (x > a)
        {
            b = a;
            a = x;
        }
        else if (x > b) b = x;
        if (x < d)
        {
            c = d;
            d = x;
        }
        else if (x < c) c = x;
    }
    if ((n == 2) && (b == 0) && (c == 0)) printf("%lld %lld",d,a);
    else if ((a * b > c * d) || ((a * b == c * d) && (a + b <= c + d))) printf("%lld %lld",b,a);
    else if ((a * b < c * d) || ((a * b == c * d) && (a + b >= c + d))) printf("%lld %lld",d,c);

 /*   if (a * b == c * d) printf("%d %d",(a + b > c + d) ? (d,c) : (b,a));
    else printf("%d %d",(a * b > c * d) ? (b,a) : (d,c));*/
    return 0;
}
