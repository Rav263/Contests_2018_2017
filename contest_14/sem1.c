#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>


enum 
{
    KEY = 123445
};

int work(int proc_id, int sem_id, int *ptr) {
    while (1) {
        struct sembuf sops[] = {
            { .sem_num = proc_id, .sem_op = -1, .sem_flg = 0 } // Операция dowm
        };

        int r = semop(sem_id, sops, sizeof(sops) / sizeof(sops[0]));

        if (r < 0) {
            fprintf(stderr, "semop: %s\n", strerror(errno));
            return 1;
        }
        printf("%d %d\n", getpid(), (*ptr)++);

        struct sembuf sops2[] = {
            { .sem_num = 1 - proc_id, .sem_op = 1, .sem_flg = 0 } //операция up
        };

        semop(sem_id, sops2, sizeof(sops2) / sizeof(sops2[0]));
    }
}


void sigint_handler(int s) {
}


int main() {

    sigaction(SIGINT, &(struct sigaction) {.sa_flags = SA_RESTART, .sa_handler = sigint_handler}, NULL);

    int *ptr = mmap(NULL, sizeof(*ptr), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    if (ptr == MAP_FAILED) {
        fprintf(stderr, "mmap: %s\n", strerror(errno));
        return 1;
    }

    int sem_id = semget(KEY, 2, IPC_CREAT | IPC_EXCL | 0600);

    if (sem_id < 0) {
        fprintf(stderr, "semget: %s\n", strerror(errno));
        return 1;
    }

    semctl(sem_id, 0, SETVAL, 1);

    if (!fork()) {
        work(0, sem_id, ptr);
        _exit(0);
    }

    if (!fork()) {
        work(1, sem_id, ptr);
        _exit(0);
    }


    while (wait(NULL) > 0) {
    }

    free(ptr);

    return 0;
}
