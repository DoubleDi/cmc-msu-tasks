#include<stdio.h>
#include<string.h>

int main(void)
{
    unsigned int number, mask = 65536 / 2;
    char key[17];
    int countzero = 0;
    scanf("%u", &number);
    key[0] = '\0';
    while (mask)
    {
       if (!(number & mask)) countzero++;
       else
       {
           if (countzero == 0) strcat(key, "a");
           if (countzero == 1) strcat(key, "b");
           if (countzero == 2) strcat(key, "c");
           countzero = 0;

       }
       if ((!(countzero % 3)) && (countzero))
       {
           strcat(key, "d");
           countzero = 0;
       }
       mask >>= 1;
    }
    if (countzero) printf("NO");
    else puts(key);
    return 0;
}
