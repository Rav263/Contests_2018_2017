#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

enum 
{
    RETURN_CODE = 42,
};

int main(int argc, char *argv[]) {
    if (argc < 5) {
        return 0;
    }
    

    if (!fork()){
        int infd = open(argv[2], O_RDONLY);
        int outfd = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0660);
        int errfd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0660);
        
        if (infd < 0|| outfd < 0 || errfd < 0) {
            return RETURN_CODE;
        }

        if (dup2(infd, 0) < 0 || dup2(outfd, 1) < 0 || dup2(errfd, 2) < 0) {
            return RETURN_CODE; 
        }

        execlp(argv[1], argv[1], NULL);
        return RETURN_CODE;
    } else {
        int code;
        wait(&code);

        printf("%d\n", code);
    }
    return 0;
}
