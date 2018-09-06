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
    DEC = 10, 
    MAX_L = 1000
};

int 
main(int arc, const char * argv[])
{
    int addr = 0, ca_addr;
    long miss = 0;
    char let, di;
    char str[MAX_L];
    long ca_size = strtol(argv[2], NULL, DEC);
    long bl_size = strtol(argv[3], NULL, DEC);
    int ca_num = ca_size / bl_size;
    int *ca_table = calloc(ca_num, sizeof(*ca_table));
    for(int i = 0; i < ca_num; i++) {
        ca_table[i] = -1;
    }
    while (fgets(str, sizeof(str), stdin)) {
        sscanf(str, "%c%c%x\n", &let, &di,  &addr);
        ca_addr = addr / bl_size;
        ca_addr = ca_addr % ca_num;
        if (ca_table[ca_addr] != addr / bl_size / ca_num) {
            if (ca_table[ca_addr] != -1) {
                miss++;
            }
            ca_table[ca_addr] = addr / bl_size / ca_num;
        }
    }
    printf("%ld\n", miss);
    return 0;
}
