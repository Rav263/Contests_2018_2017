#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdint.h>


int main(void) {
    int pid_1;
    int fds[2];

    if (pipe(fds) < 0) {
        return 1;
    }

    if ((pid_1 = fork()) == 0) {
        int pid_2;

        if ((pid_2 = fork()) == 0) {
            close(fds[1]);
            long long sum = 0;
            
            while (1) {
                unsigned int now = 0;
                int state = 0;
                for (int i = sizeof(now) - 1; i >= 0; i--) {
                    uint8_t some;
                    if (read(fds[0], &some, sizeof(some)) != sizeof(some)) {
                        state = 1;
                        break;
                    }
                    unsigned int tmp = some;
                    now <<= CHAR_BIT;
                    now += tmp;
                }
                if (state) break;
                sum += (int)now;
            }
            close(fds[0]);

            printf("%lld\n", sum);
            fflush(stdout);

            exit(0);
        } else {
            close(fds[0]);
            close(fds[1]);

            waitpid(pid_2, NULL, 0);
            exit(0);
        }   
    } else {
        close(fds[0]);

        int now;

        while (scanf("%d", &now) == 1) {
            for (int i = 0; i < sizeof(now); i++) {
                unsigned char some = (now & 0xFF000000) >> (CHAR_BIT * 3);
                now <<= CHAR_BIT;
                write(fds[1], &some, sizeof(some));
            }
        }

        close(fds[1]);

        waitpid(pid_1, NULL, 0);

        exit(0);
    }


}
