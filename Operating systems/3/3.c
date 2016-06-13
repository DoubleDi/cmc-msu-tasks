#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

struct node
{
    int key;
    int left_idx;
    int right_idx;
};

void
read_file(int fd, void *p, size_t sz)
{
    char *pp = p;
    ssize_t read_size;
    while (sz > 0) {
        read_size = read(fd, pp, sz);
        sz -= read_size;
        pp += read_size;
    }
}

void
min_print(int fd, int index)
{
    struct node pp;
    lseek(fd, sizeof(pp) * index, SEEK_SET);
    read_file(fd, &pp, sizeof(pp));
    if (pp.right_idx) {
        min_print(fd, pp.right_idx);
    }
    printf("%d ", pp.key);
    if (pp.left_idx) {
        min_print(fd, pp.left_idx);
    }
}

int
main(int argc, const char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    min_print(fd, 0);
    printf("\n");
    close(fd);
    return 0;
}
