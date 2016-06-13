
#include <stdio.h>
#include <stdlib.h>

#define ERROR_FILE_OPEN -3

struct Data
{
    int x;
    long long y;
};

void main() {
    FILE *output = NULL;
    int number;

    output = fopen("file.bin", "wb");
    if (output == NULL) {
        printf("Error opening file");
        exit(ERROR_FILE_OPEN);
    }

    struct Data s[3];


    s[0].x = 1;
    s[1].x = 1;
    s[2].x = 1;
    s[0].y = 3;
    s[1].y = 3;
    s[2].y = 3;
    fwrite(s, sizeof(struct Data), 3, output);
    fclose(output);
}
