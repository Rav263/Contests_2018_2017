#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int mysys(const char *cmd){
    int pid;
    if (!(pid = fork())) {
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        _exit(127);
    } else if (pid == -1) {
        return -1;
    } else {
        int code;
        waitpid(pid, &code, 0);

        if (WIFSIGNALED(code)) {
            return 128 + WTERMSIG(code);
        } else {
            return WEXITSTATUS(code);
        }
    }
}
