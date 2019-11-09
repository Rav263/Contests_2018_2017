#include <stdio.h>

//Окончательная версия программы

int
main(int argc, char *argv[])
{
    long long int negative_n = 0;
    long long int positive_n = 0;


    for (int i = 1; i < argc; i++) { 
        int now;

        if (sscanf(argv[i], "%d", &now) != 1) {
            return 1;
        }

        if (now < 0) {
            negative_n += now;
        } else {
            positive_n += now;
        }
    }

    printf("%lld\n%lld\n", positive_n, negative_n);

    return 0;
}
