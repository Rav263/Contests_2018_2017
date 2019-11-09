#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdlib.h>

int work(int proc_id, int sem_id, int nproc) {
    while (1) {
        struct sembuf sops[] = {
            { .sem_num = proc_id, .sem_op = -1, .sem_flg = 0 }
        };

        int r = semop(sem_id, sops, sizeof(sops) / sizeof(sops[0]));

        if (r < 0) {
            return 0;
        }

        int now;
        if (scanf("%d", &now) != 1) {
            break;
        }

        printf("%d %d\n", proc_id, now);
        fflush(stdout);

        int new_proc = now % nproc;
        
        if (new_proc < 0) {
            new_proc = nproc + new_proc;
        }

        struct sembuf sops2[] = {
            { .sem_num = new_proc, .sem_op = 1, .sem_flg = 0 } 
        };

        semop(sem_id, sops2, sizeof(sops2) / sizeof(sops2[0]));
    }
    semctl(sem_id, nproc, IPC_RMID);
    
    return 0;
}


int main(int argc, char *argv[]) {
    int nproc = atoi(argv[1]);
    int key = ftok(argv[0], 'r');

    setvbuf(stdin, NULL, _IONBF, 0);

    int sem_id = semget(key, nproc, IPC_CREAT | 0600);

    for (int i = 0; i < nproc; i++) {
        if (!fork()) {
            work(i, sem_id, nproc);
            _exit(0);
        }
    }
    struct sembuf sops2[] = {
        { .sem_num = 0, .sem_op = 1, .sem_flg = 0 } 
    };

    semop(sem_id, sops2, sizeof(sops2) / sizeof(sops2[0]));
    
    while (wait(NULL) != -1) {
    }
   
    return 0;
}
