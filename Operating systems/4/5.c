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
#include <ctype.h>

enum { MIN_SIZE = 10 };


void
go_in(void)
{
    char **dirs = calloc(MIN_SIZE, sizeof(*dirs));
    int capacity = MIN_SIZE, index = 0;
    DIR *d = opendir(".");
    if (!d) {
        return;
    }
    struct stat stb;
    struct dirent *dd;
    char *tmp;
    while ((dd = readdir(d)) != NULL) {
        if ((lstat(dd->d_name, &stb) != -1) && (strcmp(dd->d_name, ".") != 0) && (strcmp(dd->d_name, "..") != 0)
        && S_ISDIR(stb.st_mode)) {
            if (capacity == index) {
                capacity *= 2;
                dirs = realloc(dirs, capacity * sizeof(*dirs));
            }
            dirs[index++] = strdup(dd->d_name);
        }
    }
    closedir(d);
    for (int i = 0; i < index; i++) {
        for (int k = 0; k < index - i - 1; k++)
        {
            if (strcasecmp(dirs[k], dirs[k + 1]) > 0) {
                tmp = dirs[k];
                dirs[k] = dirs[k + 1];
                dirs[k + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < index; i++) {
        d = opendir(dirs[i]);
        if (d != NULL) {
            closedir(d);
            if (chdir(dirs[i]) < 0) {
                return;
            }
            printf("cd %s\n", dirs[i]);
            go_in();
            free(dirs[i]);
            if (chdir("..") < 0) {
                return;
            }
            printf("cd ..\n");
        }
    }
    free(dirs);
}


int
main(int argc, const char *argv[])
{
    if (argc == 0) return 0;
    if (chdir(argv[1]) < 0) return 0;
    go_in();
    return 0;
}
