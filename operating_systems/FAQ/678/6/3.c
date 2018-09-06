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
#include <time.h>

enum { FIRST = 100 };

int
main(void)
{
    int num, gen_num, seed, gen_rand, index = 0;
    int numarr[100][2];
    double ran;
    if (!scanf("%d", &num)) {
        return 0;
    }
    for(int i = 0; i < num; i++) {
        if (!scanf("%d %d", &numarr[i][0], &numarr[i][1])) {
            return 0;
        }
    }
    if (!scanf("%d", &gen_num)) {
        return 0;
    }
    if (!scanf("%d", &seed)) {
        return 0;
    }
    srand(seed);
    for (int i = 0; i < gen_num; i++) {
        ran = rand() / (RAND_MAX + 1.0);
        gen_rand = (int)(ran * FIRST);
        gen_rand -= numarr[0][1];
        while (gen_rand >= 0) {
            index++;
            gen_rand -= numarr[index][1];
        }
        printf("%d\n", numarr[index][0]);
        index = 0;
    }
    
    
}

