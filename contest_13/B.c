#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    //if (argc < 4) {
     //   return 1;
    //}

    int pid_1;

    int count = atoi(argv[1]);
    int modulo = atoi(argv[2]);

    int fds_out[2];
    pipe(fds_out);

    if ((pid_1 = fork()) == 0) {
        printf("SON 1 STARTED\n");
        int pid_2;

        int fds[2];

        pipe(fds);
        if ((pid_2 = fork()) == 0) {
            printf("SON 2 STARTED\n");
            close(fds[1]);
            close(fds_out[0]);

            dup2(fds[0], 0);
            dup2(fds_out[1], 1);

            execlp(argv[3], argv[3], NULL);
            printf("SOME SHIT GOING\n");

            exit(1);
        } else {
            close(fds_out[0]);
            close(fds_out[1]);
            close(fds[0]);
            for (int i = 1; i <= count; i++) {
                int x = (i * i) % modulo;
                write(fds[1], &x, sizeof(x));
            }

            close(fds[1]);
            waitpid(pid_2, NULL, 0);
            printf("SON 2 ENDED\n");
        }
    } else {
        int pid_3;
        if ((pid_3 = fork()) == 0) {
            printf("SON 3 STARTED\n");
            int pid_4;
            if ((pid_4 = fork()) == 0) {
                printf("SON 4 STARTED\n");
                close(fds_out[1]);
                char now;

                while (read(fds_out[0], &now, sizeof(now))) {
                    if (now == ' ') {
                        printf("\n");
                    } else {
                        putchar(now);
                    }
                }

                close(fds_out[1]);
            } else {
                close(fds_out[1]);
                close(fds_out[0]);
                waitpid(pid_4, NULL, 0);
                printf("SON 3 ENDED\n");
            }
        } else {
            close(fds_out[0]);
            close(fds_out[1]);
            waitpid(pid_1, NULL, 0);
            waitpid(pid_3, NULL, 0);
        }
    }
}
