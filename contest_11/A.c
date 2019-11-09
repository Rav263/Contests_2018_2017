#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
enum 
{
    MAX_STRING_SIZE = 80,
};


void print_time(int pid, char *form_str, int fd) {
    char buf[MAX_STRING_SIZE];
    waitpid(pid, NULL, 0);

    time_t now_t;
    read(fd, &now_t, sizeof(now_t));
                
    struct tm tm = {};
    tm = *localtime(&now_t);

    strftime(buf, MAX_STRING_SIZE, form_str, &tm);
    printf("%s\n", buf);
    fflush(stdout);
}



int main(void) {
    int fds[2];

    if (pipe(fds) < 0) {
        return 1;
    }


    int pid_1;
    if ((pid_1 = fork()) == 0) {
        int pid_2;
        if ((pid_2 = fork()) == 0) {
            int pid_3;
            if ((pid_3 = fork()) == 0) {
                time_t now_time = time(0);
                close(fds[0]);

                for (int i = 0; i < 3; i++) {
                    write(fds[1], &now_time, sizeof(now_time));
                }
                close(fds[1]);
                exit(0);
            } else {
                print_time(pid_3, "D:%e",fds[0]);
                exit(0);
            }
        } else {
            print_time(pid_2, "M:%m", fds[0]);
            exit(0);
        }
    } else {
        print_time(pid_1, "Y:%Y", fds[0]);
        exit(0);
    }
}

