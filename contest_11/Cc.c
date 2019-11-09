#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>



int proc(char *name, char *file_in, char *file_out) {
    int pid;
    if ((pid = fork()) == 0) {
        int fd_in = 0;
        int fd_out = 1;
        if (file_in != NULL) {
            fd_in = open(file_in, O_RDONLY);
            dup2(fd_in, 0);
            close(fd_in);
        } else if (file_out != NULL) {
            fd_out = open(file_out, O_WRONLY | O_APPEND | O_CREAT, 0600);
            dup2(fd_out, 1);
            close(fd_out);
        }


        execlp(name, name, NULL);

        exit(1);
    }
    int status;

    waitpid(pid, &status, 0);

    return WIFEXITED(status) && !WEXITSTATUS(status);
}



int main(int argc, char *argv[]) {
    if (argc < 6) {
        return 1;
    }

    int fds[2];

    pipe(fds);

    int son_pid;

    if ((son_pid = fork()) == 0) {
        close(fds[0]);
        dup2(fds[1], 1);
        close(fds[1]);
        if (proc(argv[1], argv[4], NULL)) {
            proc(argv[2], NULL, NULL);
        }
        exit(0);
    } else {
        close(fds[1]);
        dup2(fds[0], 0);
        close(fds[0]);
        proc(argv[3], NULL, argv[5]);
        waitpid(son_pid, NULL, 0); 
    }

    return 0;
}
