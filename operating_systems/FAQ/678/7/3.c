#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <sys/wait.h>



int
main(void)
{
    char s[1000];
    int start, fin, sum = 0;
    while(fgets(s, 1000, stdin)){
        sscanf(s, "%x-%x", &start, &fin);
        sum += (fin - start);
    }
    printf("%d", sum);
    return 0;
}
