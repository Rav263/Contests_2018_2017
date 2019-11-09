#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int proc(int num, int max, int *fds_in, int *fds_out) {
    int pid = fork();

    if (pid == -1) {
        exit(1);
    } else if (pid == 0) {
        close(fds_in[1]);
        close(fds_out[0]);
            
        FILE *in = fdopen(fds_in[0], "r");
        FILE *out = fdopen(fds_out[1], "w");
    
        while (1) {
            int now;
            if (fscanf(in, "%d", &now) != 1) {
                fclose(in);
                fclose(out);
                close(fds_in[0]);
                close(fds_out[1]);
                exit(0);
            }
            if (now == max) {
                fclose(in);
                fclose(out);
                close(fds_in[0]);
                close(fds_out[1]);
                exit(0);
            }

            printf("%d %d\n", num, now);
            fflush(stdout);

            now += 1;

            fprintf(out, "%d\n", now);
            fflush(out);
        }
        exit(0);
    }

    return pid;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    int max = atoi(argv[1]);

    int fds_1[2];
    int fds_2[2];

    pipe(fds_1);
    pipe(fds_2);

    /*int pid_1 =*/ proc(1, max, fds_1, fds_2);
    /*int pid_2 = */proc(2, max, fds_2, fds_1);

    FILE *out = fdopen(fds_1[1], "w");

    fprintf(out, "1\n");
    fflush(out);
    fclose(out);
    close(fds_1[0]);
    close(fds_1[1]);
    close(fds_2[0]);
    close(fds_2[1]);

    wait(NULL);
    wait(NULL);

    printf("Done\n");
    return 0;
}
