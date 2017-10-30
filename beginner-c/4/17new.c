#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define X 2000001

int duval(char *s)
{
    int j, k, m = 0;
    int i = 0, len = strlen(s);
    while (i < len)
    {
        j = i + 1;
        k = i;
        while ((j < len) && (s[k] <= s[j]))
            {
                if (s[k] < s[j]) k = i;
                else k++;
                j++;
            }
        while (i <= k)
        {
            i += j - k;
            m++;
        }
    }
    return m;
}


int main(void)
{
    char s[X], final[X];
    int w, v, tmp,len, min = -1, p = 0;
    scanf("%s", s);
    len = strlen(s);
    for (w = 0; w < strlen(s); w++)
    {
        p = duval(s);
        if ((min == -1) || (p < min))
        {
            min = p;
            final[0] = '\0';
            strcpy(final, s);
        }
        tmp = s[len - 1];
        for(v = len - 2; v >= 0; v--)
        s[v + 1] = s[v];
        s[0] = tmp;
    }
    puts(final);
    return 0;
}
