#include <stdio.h>

//Конечный вариант задачи

const double UP_LIMIT = 5.0;
const double DOWN_LIMIT = 2.0;
const double LEFT_LIMIT = 1.0;
const double RIGHT_LIMIT = 7.0;
const double LINE_OFFSET = 10.0;

int
main(void)
{
    double x, y;

    if (scanf("%lf%lf", &x, &y) != 2) {
        return 1;
    }

    int is_in_area = x <= RIGHT_LIMIT && x >= LEFT_LIMIT 
            && y <= UP_LIMIT && y >= DOWN_LIMIT && y <= LINE_OFFSET - x;

    printf("%d\n", is_in_area);

    return 0;
}
