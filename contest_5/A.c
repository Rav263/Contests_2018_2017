#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <endian.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "NO_ARGUMENT\n");
        return 1;
    }

    int fd = open(argv[1], O_RDWR);

    if (fd < 0) {
        fprintf(stderr, "NO_FILE\n");
        return 1;
    }

    long long min;
    long long min_pos = 0;

    ssize_t r = read(fd, &min, sizeof(min));

    if (r == 0) {
        close(fd);
        return 0;
    }

    if (r != sizeof(min)) {
        close(fd);

        return 1;
    }

    int now_pos = 1;

    while (1) {
        long long now;

        r = read(fd, &now, sizeof(now));

        if (r == 0) {
            break;
        }
        if (r != sizeof(min)) {
            fprintf(stderr, "READ_ERROR\n");

            close(fd);
            return 1;
        }

        if (now < min) {
            min = now;
            min_pos = now_pos;
        }

        now_pos++;
    }

    min = -(unsigned long long)min;

    if (lseek(fd, sizeof(min) * min_pos, SEEK_SET) < 0) {
        return 1;
    }

    if (write(fd, &min, sizeof(min)) != sizeof(min)) {
        close(fd);
        fprintf(stderr, "WRITE_ERROR\n");
        return 1;
    }

    close(fd);
    
    return 0;
}
