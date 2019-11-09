#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


volatile int last = 0;
volatile int count = 0;


void signal_1(int c) {
    signal(SIGINT, signal_1);

    count += 1;
    
    if (count == 4) {
        _exit(0);
    }

    printf("%d\n", last);
    fflush(stdout);
}

void signal_2(int c) {
    signal(SIGTERM, signal_2);

    _exit(0);
}


int check_num(int num) {
    for (int i = 2; i * i < num; i++) {
        if (num % i == 0) return 0;
    }

    return 1;
}


int main(int argc, char *argv[]) {
    signal(SIGINT, signal_1);
    signal(SIGTERM, signal_2);

    int low;
    int high;

    scanf("%d %d", &low, &high);

    printf("%d\n", getpid());
    fflush(stdout);

    for (int i = low; i < high; i++) {
        if (check_num(i)) last = i;        
    }


    printf("%d\n", -1);
    fflush(stdout);


    return 0;
}
