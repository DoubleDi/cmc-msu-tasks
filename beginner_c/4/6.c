#include <stdio.h>
#include <string.h>


int main(void)
{
    long int n, i, k = 0, ost = 0, len;
    char s[1000001];
    scanf("%ld\n", &n);
    scanf ("%[^\n]", s);
    len = strlen(s);
    for(i = 1; i < len; i++)
        if (s[i] == ' ') k++;
        ost = (n - len) % k;
        n = (n - len) / k;
        i = 0;
    while (i < len)
    {
        putchar(s[i]);
        if (s[i] == ' ')
        {
            for(k = 0; k < n; k++)
                    putchar(' ');
            if (ost)
            {
                putchar(' ');
                ost--;
            }
        }
        i++;
    }
    return 0;
}
