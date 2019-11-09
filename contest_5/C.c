#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum
{
    YEAR = 1900
};


int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL) {
        return 1;
    }

    struct tm now_time = {0};

    int first_run = 1;

    time_t last_time = 0;


    while (fscanf(f,"%d/%d/%d %d:%d:%d", &now_time.tm_year, &now_time.tm_mon,
                &now_time.tm_mday, &now_time.tm_hour, &now_time.tm_min, &now_time.tm_sec) == 6) {

        now_time.tm_year -= YEAR;
        now_time.tm_mon  -= 1;
        now_time.tm_isdst = -1;
        time_t now_sec_time = mktime(&now_time);

        if (!first_run) {
            time_t now_diff = difftime(now_sec_time, last_time);
            last_time = now_sec_time;

            printf("%ld\n", now_diff);
        } else {
            first_run = 0;
            last_time = now_sec_time;
        }
        memset(&now_time, 0, sizeof(now_time));
    }

    return 0;

}



