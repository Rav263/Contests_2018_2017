#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


void f_error(int *pids) {
    for (int i = 0; pids[i] != 0; i++) {
        kill(pids[i], SIGKILL);
    }

    free(pids);
    close(0);

    while (wait(NULL) != -1) {
    }

    exit(1);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    int *pids = calloc(argc - 1, sizeof(*pids));

    int fds[2];
    for (int i = 1; i < argc; i++) {

        if (pipe(fds) < 0) {
            f_error(pids);
        }

        if ((pids[i - 1] = fork()) == -1) {
            close(fds[0]);
            close(fds[1]);
            f_error(pids);
        } else if (pids[i - 1] == 0) {
            if (i < argc - 1 && dup2(fds[1], 1) < 0) {
                exit(1);
            }
            close(fds[0]);
            close(fds[1]);

            execlp(argv[i], argv[i], NULL);
            exit(1);
        } else {
            if (dup2(fds[0], 0) < 0) {
                close(fds[0]);
                close(fds[1]);
                f_error(pids);
            }
            close(fds[0]);
            close(fds[1]);
        }
    }

    close(0);
    while(wait(NULL) != -1) {
    }

    free(pids);

    return 0;
}
