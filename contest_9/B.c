#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void) {
    int pid_1 = fork();
    if (!pid_1) {
        int pid_2 = fork();
        if (!pid_2) {
            printf("3 ");
            fflush(stdout);
        }else {
            wait(NULL);
            printf("2 ");
            fflush(stdout);
        }
    } else {
        wait(NULL);
        printf("1\n");
        fflush(stdout);
    }
}
