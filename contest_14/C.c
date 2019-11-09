#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/wait.h>

struct Message
{
    long mtype;
    unsigned long long x;
    unsigned long long y;
};


int proc(int proc_id, int msgid, long long max_val, int n) {
    while (1) {
        struct Message Message;

        if (msgrcv(msgid,(void *)(&Message), 16, proc_id + 1, 0) < 0) {
            _exit(0);
        }

        unsigned long long answer = Message.x + Message.y;
        unsigned long long tmp = Message.y;


        printf("%d %llu\n", proc_id, answer);
        fflush(stdout);

        if (answer > max_val) {
            msgctl(msgid, IPC_RMID, NULL);
            return 0;
        }
        
        Message.mtype = answer % n + 1;
        Message.x = tmp;
        Message.y = answer;

        msgsnd(msgid, (void *) (&Message), 16, 0);
    }
}


int main(int argc, char *argv[]) {
    if (argc < 6) {
        return 0;
    }

    int key = atoi(argv[1]);
    int n = atoi(argv[2]);

    unsigned long long val1 = strtoll(argv[3], NULL, 10);
    unsigned long long val2 = strtoll(argv[4], NULL, 10);
    unsigned long long max_val = strtoll(argv[5], NULL, 10);

    int msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);

    int *pids = calloc(n, sizeof(*pids));


    for (int i = 0; i < n; i++) {
        if ((pids[i] = fork()) == 0) {
            proc(i, msgid, max_val, n); 
            _exit(0);
        } else if (pids[i] == -1) {
            for (int j = 0; j < i; j++) {
                kill(pids[j], SIGKILL);
            }
            
            msgctl(msgid, IPC_RMID, NULL);

            return 1;
        }
    }


    struct Message Message;
    Message.mtype = 1;
    Message.x = val1;
    Message.y = val2;

    msgsnd(msgid, (void *) (&Message), 16, 0);

    while (wait(NULL) > 0) {
    }

    free(pids);
    msgctl(msgid, IPC_RMID, 0);
}

