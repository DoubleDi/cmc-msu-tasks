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

void
common_dir(const char *d1, const char *d2, char *out)
{
    const char *pd1 = d1, *pd2 = d2;
    char *pout = out;
    while (*pd1 && *pd1 == *pd2) {
        *pout = *pd1;
        pout++;
        pd1++;
        pd2++;
    }
    *pout = 0;
    if (((!*pd1) || (*pd1 == '/')) && ((!*pd2) || (*pd2 == '/'))) {
        return;
    }
    while (*pout != '/') {
        pout--;
    }
    if (out == pout) {
        pout++;
    }
    *pout = 0;
}


#ifdef DEBUG
int
main(void)
{
    char a[10] = "/ad/bc";
    char b[10] = "/ab/bd";
    char out[10] = "";
    common_dir(a, b, out);
    puts(out);
}
#endif
