#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>



int main(int argc, char *argv[]) {
    if (argc < 6) {
        return 1;
    }
    int an_pid;
    int fds[2];

    pipe(fds);


    if ((an_pid = fork()) == 0) {
        close(fds[0]);
        dup2(fds[1], 1);
        int pid_1;
        if ((pid_1 = fork()) == 0) {
            int fd = open(argv[4], O_RDONLY);

            dup2(fd, 0);

            execlp(argv[1], argv[1], NULL);
            exit(1);
        }

        int status;
        waitpid(pid_1, &status, 0);

        if (WEXITSTATUS(status) == 0) {
            int pid_2;
            if ((pid_2 = fork()) == 0) {
                execlp(argv[2], argv[2], NULL);
                exit(1);
            }
    
            waitpid(pid_2, NULL, 0);
        }
        close(fds[1]);
        exit(0);
    } else {
        int pid_3;
        if ((pid_3 = fork()) == 0) {
            close(fds[1]);
            int fd = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0600);

            dup2(fd, 1);
            dup2(fds[0], 0);


            execlp(argv[3], argv[3], NULL);
            exit(1);
        } else {
            waitpid(pid_3, NULL, 0);
            close(fds[0]);
        }
        waitpid(an_pid, NULL, 0);
        exit(0);
    }
}
