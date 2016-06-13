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
issuffix (char *str,const char *suff)
{
    if (strlen(suff) > strlen(str)) {
        return 0;
    }
    return !strcmp(str + strlen(str) - strlen(suff), suff);
}

int
main(int argc, const char *argv[])
{
    DIR *d = opendir(argv[1]);
    if (!d) {
        return 0;
    }
    long long need_size = atoi(argv[2]);
    long long size = 0, max_size = 0;
    char max_file[PATH_MAX] = {};
    struct dirent *dd;
    struct stat stb;
    char path[PATH_MAX] = {};
    while ((dd = readdir(d)) != NULL) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", argv[1], dd->d_name);
        if ((lstat(path, &stb) != -1) && (S_ISREG(stb.st_mode))) {
            size += stb.st_size;
            if (stb.st_size >= max_size && issuffix(dd->d_name, argv[3])) {
                if (((strcmp(max_file, dd->d_name) > 0 && stb.st_size == max_size)
                || (stb.st_size > max_size))) {
                    snprintf(max_file, sizeof(max_file), "%s", dd->d_name);
                }
                max_size = stb.st_size;
            }
        }
    }
    if (size > need_size) {
        puts(max_file);
    }
    closedir(d);
}
