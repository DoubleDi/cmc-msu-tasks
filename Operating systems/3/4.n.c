#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

typedef enum Size
{
    STRUCT_SIZE = 12,
    X_SIZE = 4,
    Y_SIZE = 8
} Size;

typedef struct Item
{
    int x;
    long long y;
} Item;

void safe_read (int fd, char* buffer, int buf_size)
{
    int scan = 0;
    while (scan < buf_size){
    scan += read (fd, buffer+scan, buf_size-scan);
    }
    return;
}

void safe_write (int fd, char* buffer, int buf_size)
{
    int print = 0;
    while (print < buf_size){
    print+= write (fd, buffer+print, buf_size-print);
    }
    return;
}

void
get_struct (Item* iptr, int fd, int pos)
{
    lseek (fd, pos, SEEK_SET);
    safe_read(fd, (char*)(&iptr->x), X_SIZE);
    safe_read(fd, (char*)(&iptr->y), Y_SIZE);
    return;
}

void
write_struct (Item* iptr, int fd, int pos)
{
    lseek (fd, pos, SEEK_SET);
    safe_write(fd, (char*)(&iptr->x), X_SIZE);
    safe_write(fd, (char*)(&iptr->y), Y_SIZE);
    return;
}





int
main (int argc, const char *argv[])
{
    assert (argc > 1);
    int fd = open (argv[1], O_RDWR);
    int anum = 0;
    sscanf (argv[2], "%d", &anum);
    int end = lseek (fd, -STRUCT_SIZE, SEEK_END);
    int start = 0;
    Item first = {};
    Item second = {};

    while (end >= start){
    get_struct (&first, fd, start);
    get_struct (&second, fd, end);
    printf("first: %lld %d\n", first.y, first.x);
    printf("second: %lld %d\n", second.y, second.x);

    first.y += first.x*anum;
    second.y += second.x*anum;

    write_struct (&second, fd, start);
    write_struct (&first, fd, end);

    start += STRUCT_SIZE;
    end -= STRUCT_SIZE;

}
return 0;
}

