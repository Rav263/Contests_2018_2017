#include <time.h>
#include <stdio.h>
#include <stdlib.h>

enum 
{
    NUM_SYS = 10,
    YEAR = 1900,
    HOURS_IN_DAY = 24,
    MIN_IN_HOURS = 60,
    SEC_IN_MIN = 60,
    STRING_SIZE = 100,
    SUNDAY_INDEX = 7
};



int
main(int argc, char *argv[])
{
    if (argc < 3) {
        return 1;
    }

    long year = strtol(argv[1], NULL, NUM_SYS);
    long day = strtol(argv[2], NULL, NUM_SYS);
    
    struct tm now_time = {0};

    now_time.tm_year = year - YEAR;
    now_time.tm_isdst = -1;


    time_t now = mktime(&now_time) +  day * SEC_IN_MIN * MIN_IN_HOURS * HOURS_IN_DAY;
    localtime_r(&now, &now_time);

    char string_out[STRING_SIZE];

    strftime(string_out, sizeof(string_out), "%Y %m %d", &now_time);

    int wday = now_time.tm_wday;
    if (wday == 0) {
        wday = SUNDAY_INDEX;
    }

    printf("%s %d\n", string_out, wday);

    
    return 0;
}
