#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


volatile int mode = 0;


void sig_fir(int sign) {
    mode = 1;
}

void sig_sec(int sign) {
    mode = 2;
}


int main(int argc, char *argv[]) {
    sigset_t sigset, oldmask;
    sigemptyset(&sigset);
    
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGUSR2);

    sigprocmask(SIG_BLOCK, &sigset, &oldmask);


    sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = sig_fir, .sa_flags = 0 }, NULL);
    sigaction(SIGUSR2, &(struct sigaction) { .sa_handler = sig_sec, .sa_flags = 0 }, NULL);


    printf("%d\n", getpid());
    fflush(stdout);

    int count = 0;
    while (1) {
        sigsuspend(&oldmask);

        if (mode == 1) {
            count += 5;
            printf("%d %d\n", SIGUSR1, count);
            fflush(stdout);
        } else {
            count -= 4;
            printf("%d %d\n", SIGUSR2, count);
            fflush(stdout);
        }

        if (count < 0) {
            return 0;
        }
    }

    return 0;
}
