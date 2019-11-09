#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

enum
{
    SUM_MODE = 0,
    MUL_MODE = 1,
};


volatile int mode = SUM_MODE;

void sig_func(int sig) {
    signal(SIGINT, sig_func);
    signal(SIGQUIT, sig_func);
    if (sig == SIGINT) {
        mode = SUM_MODE;
    } else {
        mode = MUL_MODE;
    }
}


int main(void) {
    signal(SIGINT, sig_func);
    signal(SIGQUIT, sig_func);

    printf("%d\n", getpid());
    fflush(stdout);
    int now;
    int sum = 0;


    while (scanf("%d", &now) == 1) {
        if (mode == SUM_MODE) {
            sum += (long long) now;
        } else {
            sum *= (long long) now;
        }
        printf("%d\n", sum);
        fflush(stdout);
    }
}
