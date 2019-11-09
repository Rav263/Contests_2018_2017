#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <limits.h>


int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0600);

    if (fd < 0) {
        return 1;
    }

    uint32_t now;

    while (scanf("%u", &now) == 1) {
        uint8_t result_arr[sizeof(now)];

        for (int i = sizeof(now) - 1; i >= 0; i--) {
            result_arr[sizeof(now) - i - 1] = now >> (i * CHAR_BIT);
        }

        if (write(fd, &result_arr, sizeof(result_arr)) != sizeof(result_arr)) {
            return 1;
        }
    }

    close(fd);
    
    return 0;
}
