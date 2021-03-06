#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

enum { SIZE = 16 };

int
main(void)
{
    unsigned char buf[SIZE];
    int cap = 0, ind = 0;
    long long sum = 0;
    long long key, number = 0;
    long long sign = 0;// 0 == +; 1 == -
    if (cap == ind) {
        cap = read(STDIN_FILENO, buf, sizeof(buf));
        ind = 0;
    }
    if (!cap) {
        key = '*';
    } else {
        key = buf[ind++];
    }
    while((key != '*')) {
        if (key <= '9' && key >= '0') {
            key -= '0';
            number = number * 10 + key;
        } else {
            if (key == '+') {
                sign = 0;
            } else if (key == '-') {
                sign = 1;
            } else if (!sign) {
                sum += number;
                sign = 0;
            } else {
                sum -= number;
                sign = 0;
            }
            number = 0;
        }
        if (cap == ind) {
            cap = read(STDIN_FILENO, buf, sizeof(buf));
            ind = 0;
        }
        if (!cap) {
            key = '*';
        } else {
            key = buf[ind++];
        }
    }
    if (!sign) {
        sum += number;
    } else {
        sum -= number;
    }
    printf("%lld\n", sum);
}
