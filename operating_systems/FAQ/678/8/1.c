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


int main(void)
{
    printf("1");
    int status;
    /* PLACE1 */
    fflush(stdout);
    if (!fork()) {
        printf("2");
    } 
    wait(&status);
    /* PLACE2 */
    printf("3");
    return 0;
}
