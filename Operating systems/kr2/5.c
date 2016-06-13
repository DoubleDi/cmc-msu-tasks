#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>
#include <signal.h>
#include <math.h>

int
main(int argc, const char *argv[])
{
    double data, sum = 1;
    unsigned short count = 0;
    int fd = open(argv[1], O_RDONLY);
    lseek(fd, 0, SEEK_END);
    while (lseek(fd, -sizeof(count), SEEK_CUR) >= 0) {
        sum = 1;
        read(fd, &count, sizeof(count));
        lseek(fd, -sizeof(count), SEEK_CUR);
        for (int i = 0; i < count; i++) {
            lseek(fd, -sizeof(data), SEEK_CUR);
            read(fd, &data, sizeof(data));
            lseek(fd, -sizeof(data), SEEK_CUR);
            sum *= data;
        }
        if (count != 0) {
            sum = pow(sum, 1.0 / count);
        } else {
            sum = 0;
        }
        printf("%.10g\n", sum);
    }
    return 0;
}