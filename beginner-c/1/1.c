#include <stdio.h>

int main(void)
{
    int i,a,m,s,n;
    scanf("%d",&n);
    scanf("%d",&m);
    s = m;
    for (i = 0;i < n - 1;i++)
    {
        scanf("%d",&a);
        m = m > a ? m : a;
        s = s < a ? s : a;

    }
    printf("%d",m - s);
    return 0;

}
