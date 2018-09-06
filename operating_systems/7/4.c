#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <sys/wait.h>

enum {
    MAX_L = 1024,
    T1 = 10,
    T2 = 10,
    OFF = 12, 
    SZ_TABLE2 = 4096
};

int
main(void)
{
    char str[MAX_L] = {};
    int table[MAX_L] = {};
    long long start, fin, sum = 1, tb_start, tb_fin;
    while (fgets(str, sizeof(str), stdin)) {
        sscanf(str, "%llx-%llx", &start, &fin);
        tb_start = start >> (T2 + OFF);
        tb_fin = fin >> (T2 + OFF);
        while (tb_start <= tb_fin) {
            table[tb_start++] = 1;
        }
    }
    for (int i = 0; i < MAX_L; i++) {
        if (table[i] == 1) {
            sum++;
        }
    }
    printf("%lld", sum * SZ_TABLE2);
    return 0;
}
