#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main() {
    int pid;
    scanf("%d", &pid);
    int now;

    for (;scanf("%d", &now);) {
        if (now == 0) {
            kill(pid, SIGINT);
        } else {
            kill(pid, SIGQUIT);
        }
    }
}
