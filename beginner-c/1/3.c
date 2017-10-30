#include <stdio.h>

int main(void)
{
    int n;
    char c;
    scanf("%d",&n);
    while ((c = getchar()) != '.')
    {
        if (c!= ' ')
        {
             if ((c <='z') && (c >='a'))
             {
                c = (c - 'a' + n) % ('z' - 'a' + 1) + 'a';
             }
             else if ((c <='Z') && (c >='A'))
             {
                c = (c - 'A' + n) % ('Z' - 'A' + 1) + 'A';
             }
        }

        printf("%c",c);
    }
    printf("%c",c);
    return 0;
}
