#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


enum
{
    MAX_INT = 2147483647,
    MAX_INT_LEN = 10,
    EMPTY_STRING = 0x0bad1dea,
    NOT_NUMBER_STR = 0xbedabeda
};


char *getline2(FILE *f);


int 
is_number(char *string, int len, int offset)
{
    if (len < 10) {
        int now;
        sscanf(string,"%d", &now);

        return now;
    }
    if (len == MAX_INT_LEN && string[0] <= '2') {
        unsigned now;
        sscanf(string, "%u", &now);
        
        if (now <= MAX_INT) {
            return now;
        }
    }
    return offset;
}

int 
is_chars(char *string, int len)
{
    for (int i = 0; i < len; i++) {
        if (string[i] <= '0' || string[i] >= '9') {
            return 1;
        }
    }
    return 0;
}

int
calc_sum(char *string, int string_index)
{
    int index = 0;

    while (isspace(string[index])) {
        index++;
    }

    if (string[index] == 0) {
        return EMPTY_STRING + string_index;
    }

    int sum = 0;
    int offset = 1;

    for (int i = index; string[i] != 0; i++) {
        if (isspace(string[i])) {
            int modifier = 1;
            if (string[index] == '-') {
                modifier = -1;
                index += 1;
            }
            
            if (is_chars(string + index, i - index)) {
                return NOT_NUMBER_STR + string_index;
            }


            int now = is_number(string + index, i - index, offset);
            printf("%d\n", now);

            sum += now * modifier;
            offset += 1;
            index = i;
        }

        while (isspace(string[i])) {
            i++;
        }
        i -= 2;
        index = i;
    }

    return sum;
}

int
main(void)
{
    char *string = getline2(stdin);

    int sum = calc_sum(string, 1);


    printf("%d\n", sum);

    return 0;
}
