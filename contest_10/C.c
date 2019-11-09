#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int run_cmd(char *cmd_name) {
    if(!fork()) {
        execlp(cmd_name, cmd_name, NULL);
        exit(1);
    } else {
        int code;
        wait(&code);

        return WIFEXITED(code) && !WEXITSTATUS(code);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    }

    return !((run_cmd(argv[1]) || run_cmd(argv[2])) && run_cmd(argv[3]));
}
