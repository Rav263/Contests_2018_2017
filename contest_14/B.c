#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mmap.h>

int main(int argc, char *argv[]) {
    int count = atoi(argv[1]);
    int key = atoi(argv[2]);
    int nproc = atoi(argv[3]);
    int iter_count = atoi(argv[4]);

    int *first_nums = calloc(nproc, sizeof(*first_nums));

    for (int i = 0; i < nproc; i++) {
        first_nums[i] = atoi(argv[5 + i]);
    }

    int *ptr = mmap(NULL, count * sizeof(*ptr), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    if (ptr == MAP_FAILED) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        int now;

    }
}
