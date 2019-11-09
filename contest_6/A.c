#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int
main(int argc, char *argv[])
{
    unsigned long long sum = 0;
    for (int i = 1; i < argc; i++) {
        struct stat now;

        if (lstat(argv[i], &now) >= 0 && S_ISREG(now.st_mode) && now.st_nlink == 1) {
            sum += now.st_size;
        }
    }


    printf("%lld\n", sum);


    return 0;
}
