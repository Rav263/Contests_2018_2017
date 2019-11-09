#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    scanf("%d", &n);
    if (n != 1) {
        printf("1 ");
        fflush(stdout);
    } else {
        printf("1\n");
        return 0;
    }


    for (int i = 2; i <= n; i++) {
        int pid;

        if ((pid = fork()) == 0) {
            if (i != n) {
                printf("%d ", i);
            } else {
                printf("%d\n", i);
            }

            exit(0);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}
