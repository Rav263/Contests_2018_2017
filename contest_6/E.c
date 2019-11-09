#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

enum
{
    FILE_NAME_MAX = 256,
    INIT_SIZE = 8
};

int
compar(const void *a, const void *b) {
    return strcasecmp(*(char **)a, *(char **)b); 
}


void
recur_went(char *name, struct stat *st, struct dirent *dir)
{
    int size = 0;
    int real_size = INIT_SIZE;
    char **dir_names = calloc(real_size, sizeof(*dir_names));

    DIR *now_dir = opendir(name);

    if (now_dir == NULL) {
        return;
    }

    int now_len = strlen(name);


    while (1) {
        dir = readdir(now_dir);
        if (dir == NULL) {
            break;
        }

        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) {
            continue;
        }


        snprintf(name + now_len,  PATH_MAX + 2, "/%s", dir->d_name);

        lstat(name, st);

        if (S_ISDIR(st->st_mode) && !access(name, R_OK)) {
            if (size == real_size - 1) {
                real_size *= 2;
                char **tmp = realloc(dir_names, real_size * sizeof(*dir_names));

                if (tmp == NULL) {
                    return;
                }

                dir_names = tmp;
            }

            dir_names[size] = strdup(dir->d_name);
            size ++;
        }
    }

    closedir(now_dir);
    
    qsort(dir_names, size, sizeof(*dir_names), compar);

    for (int i = 0; i < size; i++) {
        printf("cd %s\n", dir_names[i]);
        snprintf(name + now_len,  PATH_MAX + 2, "/%s", dir_names[i]);
        recur_went(name, st, dir);
        printf("cd ..\n");
        free(dir_names[i]);      
    }

    free(dir_names);
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    char *fun_name = calloc(PATH_MAX + 2, sizeof(*fun_name));
    struct stat st = {};
    struct dirent dir = {}; 
    strcpy(fun_name, argv[1]);
    recur_went(fun_name, &st, &dir);
    free(fun_name);

    return 0;
}
