#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum 
{
    A = 1103515245,
    C = 12345,
    M = 2147483648,
    H = 62,
};

unsigned int next(unsigned int now) {
    return (A * now + C) % M;
}

char int_to_char(int now) {
    if (0 <= now && now < 10) {
        return now + '0';
    }
    if (10 <= now && now < 36) {
        return now + 'A' - 10;
    }
    if (36 <= now && now < 62) {
        return now + 'a' - 36;
    }
    return -1;
}

char transform(unsigned int now) {
    double tmp = now / (double) M;
    int some = tmp * H;
    //printf("%lf %d %d\n", tmp, some, now);

    return int_to_char(some);
}

int char_to_int(char now) {
    if ('0' <= now && now <= '9') {
        return now - '0';
    }
    if ('A' <= now && now <= 'Z') {
        return now - 'A' + 10;
    }
    if ('a' <= now && now <= 'z') {
        return now - 'a' + 36;
    }

    return -1;
}

unsigned int detransform(unsigned int now) {
    double tmp = now / (double) H;
    return tmp * M;
}


int main(void) {
    char string[33] = {};

    fgets(string, sizeof(string), stdin);
    int string_size = strlen(string);

    unsigned int now_low = detransform(char_to_int(string[0]));
    unsigned int now_high = detransform(char_to_int(string[0]) + 1);

    char out_string[33] = {};
    out_string[0] = string[0];
    int normal = 0;

    for (unsigned now = now_low; now < now_high; now++) {
        unsigned now_tmp = now;
        unsigned err = 0;

        for (int i = 1; i < string_size - 1; i++) {
            now_tmp = next(now_tmp);
            if (string[i] != '.') {
                char tmp = transform(now_tmp);
                if (tmp != string[i]) {
                    err = 1;
                    break;
                }
            }
        }

        if (!err) {
            if (normal == 1) {
                printf("#\n");
                return 0;
            }
            normal = 1;
            now_tmp = now;
            for (int i = 1; i < string_size - 1; i++) {
                now_tmp = next(now_tmp);
                out_string[i] = transform(now_tmp);
            }
        }
        
    }

    if (normal) {
        printf("%s\n", out_string);
    } else {
        printf("#\n");
    }

    return 0;
}
