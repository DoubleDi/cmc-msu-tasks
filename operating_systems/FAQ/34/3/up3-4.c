#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>


enum
{
    I = 4,
    LL = 8
};

struct Data
{
    int x;
    long long y;
};


void
read_file(int fd, struct Data *p)
{
    int sz = I;
    char *pp = (char *)(&p->x);
    ssize_t read_size = 0;
    while (sz > 0) {
        read_size = read(fd, pp, sz);
        pp += read_size;
        sz -= read_size;
    }
    read_size = 0;
    sz = LL;
    pp = (char *)(&p->y);
    while (sz > 0) {
        read_size = read(fd, pp, sz);
        pp += read_size;
        sz -= read_size;
    }
}


void
write_file(int fd, struct Data *p)
{
    int sz = I;
    char *pp = (char *)(&p->x);
    ssize_t write_size = 0;
    while (sz > 0) {
        write_size = write(fd, pp, sz);
        pp += write_size;
        sz -= write_size;
    }
    write_size = 0;
    pp = (char *)(&p->y);
    sz = LL;
    while (sz > 0) {
        write_size = write(fd, pp, sz);
        pp += write_size;
        sz -= write_size;
    }
}


void
print(int fd, int num)
{
    struct Data pp;
    for(int i = 0; i <= num; i++) {
        lseek(fd, i * sizeof(pp), SEEK_SET);
        read_file(fd, &pp);
        printf("%lld %d\n", pp.y, pp.x);
    }
}


int
main(int argc, const char *argv[])
{
    int fd = open(argv[1], O_RDWR);
    struct Data struct1, struct2;
    int var_a = atoi(argv[2]);
    int start_str = 0;
    int end_str = lseek(fd, -sizeof(struct1), SEEK_END);
    while (start_str <= end_str) {
        lseek(fd, start_str, SEEK_SET);
        read_file(fd, &struct1);
        struct1.y += struct1.x * var_a;
        lseek(fd, end_str, SEEK_SET);
        read_file(fd, &struct2);
        struct2.y += struct2.x * var_a;
        lseek(fd, start_str, SEEK_SET);
        write_file(fd, &struct2);
        lseek(fd, end_str, SEEK_SET);
        write_file(fd, &struct1);
        start_str += sizeof(struct1);
        end_str -= sizeof(struct1);
    }
    close(fd);
    return 0;
}
