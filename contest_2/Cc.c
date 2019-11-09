#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum 
{
    MAX_PATH_SIZE = 10000,
    NUMBERS_COUNT = 10
};


char *getline2(FILE *);

void
print_result(unsigned long long *array, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d %lld\n", i, array[i]);
    }
}


int
main(void)
{
    unsigned long long number_counts[NUMBERS_COUNT];
    for (int i = 0; i < NUMBERS_COUNT; i++) {
        number_counts[i] = 0;
    }


    char *file_path = calloc(MAX_PATH_SIZE, sizeof(*file_path));

    if (file_path == NULL) {
        fprintf(stderr, "NO FILE PATH\n");
        print_result(number_counts, NUMBERS_COUNT);
     
        return 0;
    } 


    fgets(file_path, MAX_PATH_SIZE, stdin);

    int size = strlen(file_path);
    if (file_path[size - 1] == 10 || file_path[size - 1] == 10) {
        file_path[size - 1] = 0;
    }
    if (file_path[size - 2] == 13 || file_path[size - 2] == 10) {
        file_path[size - 2] = 0;
    }

    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        free(file_path);
        fprintf(stderr, "NO FILE\n");
        print_result(number_counts, NUMBERS_COUNT);

        return 0;
    }

    char *file_data = getline2(file);

    for (int i = 0; i < strlen(file_data) + 1; i++) {
        char now = file_data[i];
        
        //printf("%d ", file_data[i]);
        
        if (now >= '0' && now <= '9') {
            number_counts[now - '0'] += 1;
        }
    }

    printf("\n");
    print_result(number_counts, NUMBERS_COUNT);
    free(file_path);

    return 0;
}
