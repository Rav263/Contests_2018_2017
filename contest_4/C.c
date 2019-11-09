#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


unsigned long long hash_function(unsigned long long);


int
main(int argc, char *argv[])
{
    if (argc < 4) {
        return 1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0660);

    if (fd < 0) {
        return 1;
    }

    unsigned long long current_h = strtoll(argv[2], NULL, 16);
    unsigned long count = strtol(argv[3], NULL, 10);
    
    if (count == 0) {
        close(fd);
        return 0;
    }


    if (lseek(fd, sizeof(current_h) * (count - 1), SEEK_END) < 0) {
        close(fd);
        return 1;
    }

    if (write(fd, &current_h, sizeof(current_h)) != sizeof(current_h)) {
        close(fd);
        return 1;
    }

    for (int i = 1; i < count; i++) {
        current_h = hash_function(current_h);

        if (lseek(fd, -2 * (long) sizeof(current_h), SEEK_CUR) < 0) {
            close(fd);
            return 1;
        }

        if (write(fd, &current_h, sizeof(current_h)) != sizeof(current_h)) {
            close(fd);
            return 1;
        }
    }

    close(fd);

    return 0;
}
