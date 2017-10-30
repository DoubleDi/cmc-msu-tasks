#include <stdio.h>

int main(void)
{
    unsigned a12,a21,a11,a22,b1,b2,ax = 0,ay = 0,i,t,c11 = 0,c12 = 0,c21 = 0,c22 = 0,c2 = 0,c1 = 0,x,y,p = 1;
    scanf("%u%u",&a11,&a12);
    scanf("%u%u",&a21,&a22);
    scanf("%u%u",&b1,&b2);
    for (i = 0;i < 32;i++)
    {

        t = 0;
        c11 = (a11 & p) >> i;
        c12 = (a12 & p) >> i;
        c21 = (a21 & p) >> i;
        c22 = (a22 & p) >> i;
        c1 = (b1 & p) >> i;
        c2 = (b2 & p) >> i;
        for (x = 0;x <= 1;x++)
            for (y = 0;y <= 1;y++)
            if ((((c11 & x) ^ (c12 & y)) == c1) && (((c21 & x) ^ (c22 & y)) == c2))
            {
                if (t == 0)
                {
                 t = 1;
                 ax = ax | x << i;
                 ay = ay | y << i;
                }
            }
        if (t == 0)
        {
            printf("No");
            break;
        }
        p <<= 1;
    }
    if (t) printf("Yes\n%u %u",ax ,ay);
    return 0;
}

