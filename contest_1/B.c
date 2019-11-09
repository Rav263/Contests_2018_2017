#include <stdio.h>

//Окончательный вариант программы

enum 
{
    NUMBERS_OFFSET = 1,
    SMALL_CH_OFFSET = 11,
    BIG_CH_OFFSET = 37,
    END_OF_RANGE = 63, 
    MASK_SB = 0xFFFB,
    MASK_TB = 0x8
};

int
main(void)
{
    int now;

    while ((now = getchar()) != EOF) {
        if (now <= '9' && now >= '0') {
            now -= '0' - NUMBERS_OFFSET;
        } else if (now <= 'z' && now >= 'a') {
            now -= 'a' - SMALL_CH_OFFSET;
        } else if (now <= 'Z' && now >= 'A') {
            now -= 'A' - BIG_CH_OFFSET;
        } else {
            continue;
        }
        now &= MASK_SB;
        now ^= MASK_TB;
       

        if (now >= NUMBERS_OFFSET && now < SMALL_CH_OFFSET) {
            now += '0' - NUMBERS_OFFSET;
        } else if (now >= SMALL_CH_OFFSET && now < BIG_CH_OFFSET) {
            now += 'a' - SMALL_CH_OFFSET;
        } else if (now >= BIG_CH_OFFSET && now < END_OF_RANGE) {
            now += 'A' - BIG_CH_OFFSET;
        } else if (now == 0) {
            now = '@';
        } else if (now == END_OF_RANGE) {
            now = '#';
        }
        putchar(now);
    }
    printf("\n");

    return 0;
}
