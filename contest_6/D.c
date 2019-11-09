#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    DIR *dr = opendir(argv[1]);

    if (dr == NULL) {
        return 1;
    }

    unsigned long long size = 0;
    unsigned uid = getuid();

    while(1) {
        struct dirent *dir = readdir(dr);

        if (dir == NULL) {
            break;
        }

        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) {
            continue;
        }

        struct stat st = {};

        char name[PATH_MAX + 2] = {};
        sprintf(name, "%s/%s", argv[1], dir->d_name);

        stat(name, &st);

        if (S_ISREG(st.st_mode) && dir->d_name[0] <= 'Z' && dir->d_name[0] >= 'A' && st.st_uid == uid) {
            size += st.st_size;
        }

    }

    printf("%lld\n", size);
}
