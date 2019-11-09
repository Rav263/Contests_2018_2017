#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum 
{
    NUMBERS_COUNT = 10,
    MAX_STRING_SIZE = 8192,
};

void
print_result(const unsigned long long *array, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d %lld\n", i, array[i]);
    }
}


int
main(void)
{
    unsigned long long number_counts[NUMBERS_COUNT];

    memset(number_counts, 0, sizeof(number_counts));

    char file_path[FILENAME_MAX + 3];


    if(fgets(file_path, sizeof(file_path), stdin) == NULL) {
        fprintf(stderr, "FILE PATH CAN'T BE READED\n");
        print_result(number_counts, NUMBERS_COUNT);        
        return 0;
    }

    int size = strlen(file_path);
    if (size > 0 && (file_path[size - 1] == '\r' || file_path[size - 1] == '\n')) {
        file_path[size - 1] = 0;
    }
    if (size > 1 && (file_path[size - 2] == '\r' || file_path[size - 2] == '\n')) {
        file_path[size - 2] = 0;
    }

    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        fprintf(stderr, "NO FILE\n");
        print_result(number_counts, NUMBERS_COUNT);

        return 0;
    }


    char now_string[MAX_STRING_SIZE];
    while (fgets(now_string, sizeof(now_string), file) != NULL) {
        for (int i = 0; now_string[i] != 0; i++) {
            if (now_string[i] >= '0' && now_string[i] <= '9') {
                number_counts[now_string[i] - '0'] += 1;
            }
        }
    }

    print_result(number_counts, NUMBERS_COUNT);

    return 0;
}
