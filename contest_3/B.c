#include <stdio.h>
#include <math.h>


enum
{
    MAX_PRECENTAGES = 100, //Максимальное изменение курса в процентах
    MAX_RATE = 10000, //Максимально возможный курс
    ROUND_VALUE = 10000 //Константа для округления курса до n знаков после запятой равная 10^n.
};


int
main(int argc, char *argv[]) 
{
    double rate;

    if (argc == 1) {
        return 1;
    }


    if (sscanf(argv[1], "%lf", &rate) != 1) {
        return 1;
    }

    for (int i = 2; i < argc; i++){
        double now;

        if (sscanf(argv[i], "%lf", &now) != 1) {
            return 1;
        }
        if (now <= -MAX_PRECENTAGES || now >= MAX_PRECENTAGES) {
            return 1;
        }

        rate *= (MAX_PRECENTAGES + now) / MAX_PRECENTAGES;
   
        rate = (double) round(rate * ROUND_VALUE) / ROUND_VALUE;

        if (rate <= 0 && rate > MAX_RATE) {
            return 1;
        }
    }

    printf("%.4lf\n", rate);

    return 0;
}
