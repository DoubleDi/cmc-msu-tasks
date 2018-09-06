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

struct MyFile
{
    int fd; // файловый дескриптор для чтения
    int size; // размер буфера (> 0)
    char *buf; // буфер (non-NULL)
    int nr;
    int ind;
};

int
mygetc(struct MyFile *f)
{
    if (f->nr == f->ind) {
        f->nr = read(f->fd, f->buf, f->size);
        f->ind = 0;
    }
    if ((!f->nr) || (f->nr == -1)) {
        return EOF;
    } else {
        return (unsigned char)(f->buf[f->ind++]);
    }
}

#ifdef DEBUG
int
main(void)
{


    return 0;
}
#endif // DEBUG
