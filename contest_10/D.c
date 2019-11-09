#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>


int main(int argc, char *argv[]) {
    int pid = getpid();

    char file_name[PATH_MAX] = {};
    char an_tmp[PATH_MAX] = "/tmp";
    char *tmp = getenv("XDG_RUNTIME_DIR");
    if (tmp == NULL) {
        tmp = getenv("TMPDIR");
        if (tmp == NULL) {
            tmp = an_tmp;
        }
    }

    snprintf(file_name, PATH_MAX, "%s/%d.sh", tmp, pid);

    FILE *file = fopen(file_name, "w+");

    if (file == NULL) {
        return 1;
    }


    fprintf(file, "#! /bin/bash\n");
    fprintf(file, "python3 -c \"print(");

    for (int i = 1; i < argc; i++) {
        fprintf(file, "%s*", argv[i]);
    }
    fprintf(file, "1)\"\n");
    fprintf(file, "rm $0\n");
    fclose(file);

    execl("/bin/sh", "sh", file_name, NULL);
}
