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


int
main(int argc,const char *argv[])
{
    char path[PATH_MAX] = {};
    struct stat stb;
    DIR *d = opendir(argv[1]);
    struct dirent *dd = NULL;
    long long size = 0;
    while ((dd = readdir(d)) != NULL) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", argv[1], dd->d_name);
        if ((lstat(path, &stb) != -1) && S_ISREG(stb.st_mode)) {
            size += stb.st_size;
        }
    }
    printf("%lld\n", size);
    closedir(d);
    return 0;
}
