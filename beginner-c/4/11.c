#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char num1[7], num2[7], input, znak = ' ', index1 = 0, index2 = 0, tmp[7];
    int output = 0, flag = 0, i, t = 0;
    num1[0] = '\0';
    num2[0] = '\0';
    scanf ("%[^\n+-*/]", tmp);
    while(tmp)
    {
        puts(tmp);

        if ((num1[0] == '\0') && (num2[0] == '\0'))
        {
            index1 = 0;
            for(i = 0; i < strlen(tmp); i++)
                if ((tmp[i] > '9') || (tmp[i] < '0')) t = i + 1;
            printf("%d\n", t);
            for(i = t; i < strlen(tmp); i++)
            {
                num1[index1] = tmp[i];
                index1++;

            }
            num1[index1] = '\0';

        }
        puts(num1);
        scanf ("%[^\n+-*/]", tmp);
        break;
        /*else if (num2[0] == '\0')
        znak = getchar();
        putchar(znak);
        */

    }


}
