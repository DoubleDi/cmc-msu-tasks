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



enum
{
    MAX_L = 1021,
    MAX_PR = 32
};

int
checkgid(unsigned *gid_p,unsigned gid, int index)
{
    for(int i = 0; i < index; i++) {
        if (gid_p[i] == gid) {
            return 1;
        }
    }
    return 0;
}


char*
getname(char *st, int numb)
{
    int len;
    char *name = NULL;
    while (isspace(st[numb])) {
        numb++;
    }
    name = strdup(&st[numb]);
    len = strlen(name);
    while (len > 0 && isspace(name[len - 1])) {
        len--;
    }
    name[len] = 0;
    return name;
}


int
checkperms(unsigned perms, unsigned need_perms)
{
    if ((perms & need_perms) == need_perms) {
        return 1;
    } else {
        return 0;
    }
}


int
main(void)
{
    char st[MAX_L] = {};
    char * name_file;
    unsigned uid_p, gid_p[MAX_PR] = {}, need_perms, perms;
    int index = 0, numb = 0, len = 0;
    unsigned uid_file, gid_file, perms_file;
    if ((scanf("%u ", &uid_p) > 0) && fgets(st, MAX_L, stdin)) {
        while (sscanf(st + len, "%u%n ", &gid_p[index], &numb) > 0) {
            len += numb;
            index++;
        }
        if (scanf("%o ", &need_perms) <= 0) {
            return 0;
        }
        while (fgets(st, MAX_L, stdin)) {
            if (sscanf(st, "%u %u %o %n", &uid_file, &gid_file, &perms_file, &numb) < 0) {
                return 0;
            }
            name_file = getname(st, numb);
            if (uid_p == uid_file) {
                perms = perms_file >> 6;
            } else if (checkgid(gid_p, gid_file, index)) {
                perms = perms_file >> 3;
            } else {
                perms = perms_file;
            }
            if (checkperms(perms, need_perms)) {
                printf("%s\n", name_file);
            }
            free(name_file);
        }
    }
    return 0;
}
