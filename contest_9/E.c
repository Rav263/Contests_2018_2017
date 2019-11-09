#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>



int main(void) {
    int first_pid = getpid();
    while (1) {
        int pid = fork();
        int now;
        if (pid == -1) {
            return 1;
        } else if (!pid) {
            if (scanf("%d", &now) != 1) {
                return 0;
            }
        } else {
            int status;
            int some_pid = getpid();
            waitpid(pid, &status, 0);

            if (WEXITSTATUS(status) == 1) {
                if (some_pid == first_pid) {
                    printf("-1\n");
                    fflush(stdout);
                    return 0;
                }
                return 1;
            } else {
                if (some_pid != first_pid) {
                    printf("%d\n", now);
                    fflush(stdout);
                }
                return 0;
            }
        }
    }
}
