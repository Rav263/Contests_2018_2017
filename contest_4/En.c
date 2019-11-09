#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};


int rec_went(int fd, int now_index) {
    struct Node now;


    if (lseek(fd, now_index * sizeof(now), SEEK_SET) < 0) {
        return -1;
    }

    if (read(fd, &now, sizeof(now)) != sizeof(now)) {
        return -1;
    }

    if (now.right_idx != 0) {
        rec_went(fd, now.right_idx);
    }
    printf("%d ", now.key);
    if (now.left_idx != 0) {
        rec_went(fd, now.left_idx);
    }
    return 0;
}


int 
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        return 1;
    }

    if (rec_went(fd, 0) < 0) {
        fprintf(stderr, "READ ERROR\n");
        close(fd);

        return 1;
    }
    printf("\n");

    close(fd);

    return 0;
}
