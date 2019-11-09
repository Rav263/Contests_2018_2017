#include <time.h>
#include <stdio.h>
#include <stdlib.h>


enum
{
    YEAR = 1900, 
    BEG_YEAR = 1925, // Начало отсчёта года в новом календаре
    BEG_MON = 10, // Начало отсчёта месяца в новом календаре
    BEG_DAY = 7,// Начало отсчёта дня в новом календаре
    SEC_IN_MIN = 60, // Количество секунд в минутах в новом календаре
    MIN_IN_HOUR = 60, // Количество минут в часах в новом календаре
    HOUR_IN_DAY = 24, // Количество часов в сутках в новом календаре
    DAYS_IN_MONTH = 30, // Количество дней в каждом месяце в новом календаре
    MONTH_IN_YEAR = 12, // Количество месяцев в году в новом календаре
    UTC = 3 //Константа для корректной работы с часовыми поясами
};

int
main(void)
{
    int year;
    int mon;
    int day;
    
    
    struct tm beg_time = {};

    beg_time.tm_year = BEG_YEAR - YEAR;
    beg_time.tm_mon = BEG_MON - 1;
    beg_time.tm_mday = BEG_DAY;
    beg_time.tm_isdst = -1;
    beg_time.tm_hour = 0;

    long long begin_time = mktime(&beg_time);
    
    while (scanf("%d%d%d", &year, &mon, &day) == 3) {
        struct tm now = {};

        now.tm_year = year - YEAR;
        now.tm_mon = mon - 1;
        now.tm_mday = day;
        now.tm_isdst = -1;
        now.tm_hour = UTC;


        long long now_time = mktime(&now); 
    
        long long new_time = now_time - begin_time;


        long long new_days = new_time / (SEC_IN_MIN * MIN_IN_HOUR * HOUR_IN_DAY);
        long long new_year = new_days / (DAYS_IN_MONTH * MONTH_IN_YEAR);
        long long new_mon = (new_days / DAYS_IN_MONTH) % MONTH_IN_YEAR;
        long long new_mday = new_days % DAYS_IN_MONTH;
        
        printf("%lld %lld %lld\n", new_year + 1, new_mon + 1, new_mday + 1);
    }

    return 0;
}
