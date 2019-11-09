#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

enum
{
    EMPTY_STRING = 0x0bad1dea,
    NOT_NUMS_STRING = 0xbedabeda
};


char *getline2(FILE *);

int
calc_sum(char *string, int string_offset, int str_len)
{
    char *ptrl = string;
    int normal = 0;
    for (int i = 0; i < str_len; i++) {
        if (!isspace((unsigned char) string[i])) {
            normal = 1;
            break;
        }
    } 

    if (!normal) {
        return EMPTY_STRING + string_offset;
    }

    int offset = 1;
    unsigned sum = 0;

    char *last_ptr = NULL;

    while (last_ptr != ptrl) {
        last_ptr = ptrl;
        long nowl = strtol(ptrl, &ptrl, 10);

        if (last_ptr == ptrl) {
            while (isspace((unsigned char) *ptrl)){
                ptrl++;
            }

            if (*ptrl != '\0') {
                return NOT_NUMS_STRING + string_offset;
            }
        }
        if (errno == ERANGE || nowl > INT_MAX || nowl < INT_MIN) {
            sum += nowl < 0 ? -offset : offset;
            errno = 0;
        } else {
            sum += nowl;
        }
        
        offset++;
    }

    return sum;
}



int
main(void)
{
    char *string;
    int string_number = 1;
    while ((string = getline2(stdin)) != NULL) {
        printf("%d\n", calc_sum(string, string_number, strlen(string)));
        free(string);
        string_number++;
    }
    return 0;
}
