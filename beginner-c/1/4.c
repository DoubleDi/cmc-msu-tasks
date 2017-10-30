#include <stdio.h>

int main(void)
{
    int i,n,p,a,t = 1,max = 0;
    scanf("%d",&n);
    scanf("%d",&p);
    for(i = 0;i < n - 1; i++)
    {
        scanf("%d",&a);
        max = a > p ? max : (t > max ? t : max);
        t = a > p ? (t + 1) : 1;
        p = a;

    }

    printf("%d", max > t ? max : t);
    return 0;
}
