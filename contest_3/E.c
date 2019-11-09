#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


enum 
{
    BUFF_SIZE = 16
};

int
main(void)
{

    int fd = 1;

    char buff[BUFF_SIZE];

    unsigned long long sum = 0;
    int is_number = 0;
    unsigned long long now_number = 0;
    int sign_flag = 0;

    while (1) {
        ssize_t r = read(fd, &buff, sizeof(buff));

        if (r < 0) {
            return 1;
        }
        if (!r) {
            break;
        }

        int index = 0;

        if (isspace(buff[index]) && is_number) {
            sum += now_number;
            now_number = 0;
            is_number = 0;
        }        

        for (; index < r;) {
            while (isspace(buff[index]) && index < r) {
                index++;
            }

            if (index == r) {
                break;
            }
            if (buff[index] == '+') {
                is_number = 1;
                sign_flag = 1;
            }
            if (buff[index] == '-') {
                is_number = 1;
                sign_flag = -1;
            }
            index ++;
            for (; index < r; index++) {
                if (isspace(buff[index])){
                    printf("%d %llu\n", sign_flag, now_number);
                    sum += sign_flag * now_number;
                    sign_flag = 0;
                    now_number = 0;
                    is_number = 0;
                    break;
                }
                unsigned int now = buff[index] - '0';
                now_number *= 10;
                now_number += now;
            }
        }
    }


    printf("%lld\n", sum);
    return 0;
}
