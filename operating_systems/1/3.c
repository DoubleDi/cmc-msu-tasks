#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
mysubstr(char * sample, char * text)
{
    int pos_star = strchr(sample, '*') - sample;
    int text_length = strlen(text);
    int sample_length = strlen(sample);
    int pos_half1 = 0, pos_half2 = 0, index = 0, key = 0, check_pos = 0;
    int half1_len = 0, half2_len = 0;
    char * half1 = calloc(pos_star, sizeof(half1));
    char * half2 = calloc(sample_length - pos_star - 1, sizeof(half2));
    half1_len = pos_star;
    memcpy(half1, sample, half1_len);
    half1[half1_len] = '\0';
    half2_len = sample_length - pos_star - 1;
    memcpy(half2, &sample[pos_star + 1], half2_len);
    half2[half2_len] = '\0';
    pos_half1 = strstr(text, half1);
    if (!pos_half1) {
        return -1;
    }
    pos_half1 -= (int)text;
    index = text_length - 1;
    key = index;
    while(index >= 0) {

        if (half2_len - check_pos - 1 < 0) {
            pos_half2 = index + 1;
            break;
        }
        if (text[index] == half2[half2_len - check_pos - 1]) {
            if(!check_pos) {
                key = index;
            }
            check_pos++;
        }
        else {
            key = index;
            index = key - 1;
            check_pos = 0;
        }
        index--;
    }
   // if (text[index] != half2[half2_len - check_pos - 1]) {
    //    return -1;
   // }
    free(half1);
    free(half2);
    printf("%d %d\n", pos_half1, pos_half2);
    if (pos_half2 - pos_half1 >= half1_len - 1) {
        if (half1_len >= 0) {
            return pos_half1 + 1;
        }
        else {
            return pos_half2 + 1;
        }
    }
    else {
        return -1;
    }
}

int
main(void)
{
    char text[1000] = "bbaaaaaaaa";
    char sample[100] = "*aa";
    printf("%d", mysubstr(sample, text));
    return 0;
}
