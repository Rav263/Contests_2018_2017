#include <stdio.h>

//Окончательный вариант

enum
{
    FRACTION_SIZE = 23
};

int
float_checker(unsigned now)
{
    int counter = 0;
    while (now != 0) {
        if (now % 2 != 0 || counter != 0) {
            counter += 1;
        }
        now >>= 1;
    }

    return counter <= FRACTION_SIZE + 1;
}



int
main(void)
{
    unsigned now;

    while (scanf("%u", &now) == 1) {
        printf("%d\n", float_checker(now));
    }

    return 0;
}
