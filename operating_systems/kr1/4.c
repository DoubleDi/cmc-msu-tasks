#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>


enum { DEC = 10 };

int
read_file(int fd, void *p, size_t sz)
{
    char *pp = p;
    ssize_t read_size;
    while (sz > 0) {
        read_size = read(fd, pp, sz);
        if (read_size <= 0) {
            return -1;
        }
        sz -= read_size;
        pp += read_size;
    }
    return sz;
}



int
main(int argc, const char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    unsigned short size;
    long long lsize = 0, number = 0, allsize = 0;
    off_t offset = strtol(argv[2], NULL, DEC);
    do {
        lseek(fd, offset, SEEK_SET);
        if (read_file(fd, &size, sizeof(size)) < 0) {
            break;
        }
        lseek(fd, size, SEEK_CUR);
        read_file(fd, &lsize, sizeof(lsize));
        number++;
        allsize += size;
        offset += lsize;
    } while (lsize != 0);
    printf("%lld\n%lld\n", number, allsize);
    close(fd);
}
