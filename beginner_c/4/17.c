#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define X 4000002




int main(void)
{
    char s[X];
    int  check = 0, len, i = 0, j, k;
    scanf("%s", s);
    len = strlen(s);
    for(k = 0; k < len; k++)
        s[len + k] = s[k];
    s[len + k + 1] = '\0';
    while (i < len)
    {
        j = i + 1;
        k = i;
        check = i;
        while ((j < 2 * len) && (s[k] <= s[j]))
            {
                if (s[k] < s[j]) k = i;
                else k++;
                j++;
            }
        while (i <= k) i += j - k;
    }
    for(k = check; k < check + len; k++)
        putchar(s[k]);
    return 0;
}
