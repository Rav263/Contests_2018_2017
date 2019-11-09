#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

enum 
{
    NUM_OF_PROC = 3,
    LINE_LEN = 8,
};


int proc(int num) {
    int pid = fork();
    
    if (!pid) {
        char string[LINE_LEN];
        read(0, string, sizeof(string));
        int x;

        x = atoi(string);

        x *= x;

        printf("%d %d\n", num, x);
        fflush(stdout);
    }

    return pid;
}


int main(void) {
    for(int i = 0; i < NUM_OF_PROC; i++) {
        if (!proc(i + 1)) {
            return 0;
        }
    }

    while (wait(NULL) != -1);
    return 0;
}
