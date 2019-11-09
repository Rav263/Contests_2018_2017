#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

volatile int max;
FILE *file_in;
FILE *file_out;


int ping_pong(int proc_num){
    int num;
    int pid;

    fscanf(file_in, "%d%d", &pid, &num);

    if (num == max) {
        fprintf(file_out, "%d\n", pid);
        fflush(file_out);
        return -1;
    }

    printf("%d %d\n", proc_num, num);
    fflush(stdout);

    num += 1;

    fprintf(file_out, "%d %d\n", getpid(), num);
    fflush(file_out);

    kill(pid, SIGUSR1);
    return 0;
}


void sig_proc_1(int sig) {
    signal(SIGUSR1, sig_proc_1);
    int num;
    int pid;

    fscanf(file_in, "%d%d", &pid, &num);

    if (num == max) {
        fprintf(file_out, "%d\n", pid);
        fflush(file_out);
        exit(0);
    }

    printf("1 %d\n", num);
    fflush(stdout);

    num += 1;

    fprintf(file_out, "%d %d\n", getpid(), num);
    fflush(file_out);
    kill(pid, SIGUSR1);
}

void sig_proc_2(int sig) {
    signal(SIGUSR1, sig_proc_2);
    int num;
    int pid;

    fscanf(file_in, "%d%d", &pid, &num);

    if (num == max) {
        fprintf(file_out, "%d\n", pid);
        fflush(file_out);
        exit(0);
    }

    printf("2 %d\n", num);
    fflush(stdout);

    num += 1;

    fprintf(file_out, "%d %d\n", getpid(), num);
    fflush(file_out);

    kill(pid, SIGUSR1);
}



int proc(void (*handler) (int)) {
    int pid = fork();

    if (pid == 0) {
        signal(SIGUSR1, handler);
        
        printf("Son started\n");
        fflush(stdout);

        while (1) {
            pause();
        }
        printf("Son охуел в край\n");
        fflush(stdout);


        exit(0);
    } else if (pid == -1) {
        fprintf(stderr, "YOU ARE IDIOT!!\n");

        return -1;
    } else {
        return pid;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    max = atoi(argv[1]);
    
    int fds[2];
    pipe(fds);
    
    file_in = fdopen(fds[0], "r");
    file_out = fdopen(fds[1], "w");

    int pid_1 = proc(sig_proc_1);
    int pid_2 = proc(sig_proc_2);

    fprintf(file_out, "%d %d\n", pid_2, 1);
    fflush(file_out);

    kill(pid_1, SIGUSR1);

    wait(NULL);
    int pid;
    fscanf(file_in, "%d\n", &pid);

    fprintf(file_out, "%d %d\n", pid, max);
    fflush(file_out);
    kill(pid, SIGUSR1);
    wait(NULL);

    printf("Done\n");

    fflush(stdout);

    fclose(file_in);
    fclose(file_out);

    close(fds[0]);
    close(fds[1]);
    return 0;
}
