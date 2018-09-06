#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <math.h>

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    unsigned short n;
    int cur_off = 0, sm;
    sm = lseek(fd, 0, SEEK_END);
    while (cur_off < sm) {
        lseek(fd, -sizeof(n) - cur_off, SEEK_END);
        read(fd, &n, sizeof(n));
        lseek(fd, -sizeof(n), SEEK_CUR);
        double mult = 1, cur;
        for (int j = 0; j < n; j++) {
            lseek(fd, -sizeof(cur), SEEK_CUR);
            read(fd, &cur, sizeof(cur));
            lseek(fd, -sizeof(cur), SEEK_CUR);
            mult *= cur;
        }
        if (n > 0) {
            double ans = pow(mult, 1.0 / n);
            printf("%.10g\n", ans);
        } else {
            printf("0\n");
        }
        cur_off += sizeof(n) + n * sizeof(cur);
    }
    return 0;
}
