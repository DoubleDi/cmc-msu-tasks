#include <stdio.h>
#include <assert.h>
#include <string.h>

void normalize_path(char * buf)
{
    int flag = 0;
    char *curr_buf = buf;
    char *new_buf = buf;
    while(*curr_buf) {
        if (*curr_buf == '/' && flag == 0) {
            flag = 1;
            *new_buf++ = *curr_buf++;
        } else if (*curr_buf == '/' && flag == 1) {
            curr_buf++;
        } else {
            *new_buf++ = *curr_buf++;
            flag = 0;
        }
    }
    while(*new_buf) {
        *new_buf++ = '\0';
    }
    //puts(buf);
}
#ifdef DEBUG
int main(int argc, const char* argv[])
{
    char buf[37] = "////////a///b//c/////d/////e////f///";
    normalize_path(buf);
    return 0;
}
#endif // DEBUG

