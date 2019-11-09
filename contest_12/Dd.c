#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


volatile int max_num;
FILE *file_in;
FILE *file_out;

void signal_1(int c) {
    signal(SIGUSR1, signal_1);

    int num;
    int pid;
    int proc_num;

    fscanf(file_in, "%d%d%d", &pid, &num, &proc_num);

    if (num == max_num) {
        fprintf(file_out, "%d\n", pid);
        fflush(file_out);

        fflush(stdout);

        _exit(0);
    }

    printf("%d %d\n", proc_num + 1, num);
    fflush(stdout);

    num += 1;

    fprintf(file_out, "%d %d %d\n", getpid(), num, 1 - proc_num);
    fflush(file_out);

    kill(pid, SIGUSR1);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    max_num = atoi(argv[1]);

    int fd[2];

    pipe(fd);

    file_in = fdopen(fd[0], "r");
    file_out = fdopen(fd[1], "w");

    int pid_1 = fork();

    if (pid_1 == 0) {
        signal(SIGUSR1, signal_1);

        while (1) {
            pause();
        }
        _exit(0);
    }

    int pid_2 = fork();

    if (pid_2 == 0) {
        signal(SIGUSR1, signal_1);

        while (1) {
            pause();
        }
        _exit(0);
    }

    while (!pid_1 || !pid_2) {
        
    }

    fprintf(file_out, "%d %d %d\n", pid_1, 1, 0);
    fflush(file_out);
    
    kill(pid_1, SIGUSR1);

    wait(NULL);
    int pid;

    fscanf(file_in, "%d", &pid);

    fprintf(file_out, "%d %d %d\n", pid, max_num, 1);
    fflush(file_out);

    kill(pid, SIGUSR1);
    wait(NULL);


    close(fd[0]);
    close(fd[1]);
    
    printf("Done\n");
    fflush(stdout);


    return 0;
}

