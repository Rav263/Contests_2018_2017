#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    int mod = atoi(argv[2]);

    int pid = getpid();

    char name[PATH_MAX + 2];
    
    snprintf(name, PATH_MAX + 2, "%d.c", pid);
    
    mkstemps(name, 2);

    FILE *file = fopen(name, "w");
    if (file == NULL) {
        return 0;
    }

    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "int main(void) {\n");
    fprintf(file, "unsigned now;\n");
    fprintf(file, "scanf(\"%%d\", &now);\n");
    fprintf(file, "int mod = %d;\n", mod);
    fprintf(file, "unsigned long long sum = now;\n");
    fprintf(file, "sum *= (now + 1);\n");
    fprintf(file, "sum /= 2;\n");
    fprintf(file, "unsigned sum_mod = sum %% mod;\n");
    fprintf(file, "printf(\"%%u\\n\", sum_mod);\n");
    fprintf(file, "return 0;\n");
    fprintf(file, "}\n");

    fclose(file);
    if (!fork()) {
        execlp("gcc", "gcc", "-O3", name, "-o", argv[1], NULL);
        exit(1);
    }

    wait(NULL);
    chmod(argv[1], 0751);
    unlink(name);
}
