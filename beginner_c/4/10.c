#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define X 2003

int prefixf(char *s1, char *s2)
{
    int mas[X], i, k = 0, index = 0, len1 = strlen(s1),len2 = strlen(s2);
    char tmp[2*X];
    mas[0] = 0;
    for(i = 0;i < len1; i++)
    {
        tmp[index] = s1[i];
        index++;
        tmp[index] = '\0';
    }
    tmp[index] = ' ';
    index++;
     for(i = 0;i < len2; i++)
    {
        tmp[index] = s2[i];
        index++;
        tmp[index] = '\0';
    }
	for(i = 1; i < len1 + len2 + 1; i++)
	{
		while((tmp[k] != tmp[i]) && (k > 0)) k = mas[k - 1];
		if(tmp[k] == tmp[i]) k++;
		mas[i] = k;
	}
    return k;
}

int main(void)
{
    char s1[X], s2[X];
    gets(s1);
    gets(s2);
    printf("%d %d", prefixf(s1, s2), prefixf(s2, s1));
    return 0;
}
