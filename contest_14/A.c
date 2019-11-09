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

int work(int proc_id, int sem_id, int *ptr, int nproc, int max_val) {
    while (1) {
        struct sembuf sops[] = {
            { .sem_num = proc_id - 1, .sem_op = -1, .sem_flg = 0 }
        };

        int r = semop(sem_id, sops, sizeof(sops) / sizeof(sops[0]));

        if (r < 0) {
            return 0;
        }
        printf("%d %d %d\n", proc_id, (*ptr), ptr[1]);
        fflush(stdout);
        ptr[1] = proc_id;

        if (*ptr == max_val ) {
            break;
        }
        (*ptr)++;

        int new_proc = *ptr % nproc;
        for (int i = 0; i < 2; i++) {
            new_proc *= new_proc;
            new_proc %= nproc;
        }
        new_proc += 1;

        struct sembuf sops2[] = {
            { .sem_num = new_proc - 1, .sem_op = 1, .sem_flg = 0 } 
        };

        semop(sem_id, sops2, sizeof(sops2) / sizeof(sops2[0]));
    }
    semctl(sem_id, 0, IPC_RMID);  


    return 0;
}


int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 0;
    }

    int nproc = atoi(argv[1]);
    int key = atoi(argv[2]);
    int max_val = atoi(argv[3]);

    int *ptr = mmap(NULL, 2 * sizeof(*ptr), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    if (ptr == MAP_FAILED) {
        return 1;
    }

    int sem_id = semget(key, nproc, IPC_CREAT | 0600);

    if (sem_id < 0) {
        fprintf(stderr, "semget: %s\n", strerror(errno));
        return 1;
    }

    semctl(sem_id, 0, SETVAL, 1);
    ptr[0] = 0;
    ptr[1] = 0;

    for (int i = 0; i < nproc; i++) {
        if (!fork()) {
            work(i + 1, sem_id, ptr, nproc, max_val);
            _exit(0);
        }
    }

    while (wait(NULL) > 0) {
        
    }
    return 0;
}
