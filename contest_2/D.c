#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>



enum
{
    MIN_ARRAY_SIZE = 512,
    MEM_OFFSET = 2,
    BUFFER_SIZE = 4096
};


typedef struct DynamicArr 
{
    unsigned int size;
    unsigned int mem_size;
    char *array;
} DynamicArr;


int
add_char(DynamicArr *array, char now)
{
    if (array->array == NULL) {
        return -1;
    }
    if (array->size == array->mem_size) {
        array->mem_size *= MEM_OFFSET;
        array->array = realloc(array->array, array->mem_size * sizeof(*(array->array)));

        if (array->array == NULL) {
            return -1;
        }
    }

    array->array[array->size] = now;
    array->size += 1;
    return 0;
}


char *
getline2(FILE *f) 
{
    DynamicArr array;

    if (f == NULL) {
        return NULL;
    }

    array.array = calloc(MIN_ARRAY_SIZE, sizeof(*(array.array)));
    array.size = 0;
    array.mem_size = MIN_ARRAY_SIZE;

    char buf[BUFFER_SIZE];

    int read_d = fileno(f);

    while (1) {
        ssize_t r = read(read_d, &buf, sizeof(buf));

        if (r < 0) {
            fprintf(stderr, "error: %s\n", strerror(errno));
            free(array.array);
            return NULL;
        }

        if (!r) {
            break;
        }
        
        for (int i = 0; i < r; i++) {
            if (buf[i] == '\n') {
                if (add_char(&array, buf[i]) < 0 || add_char(&array, 0) < 0) {
                    return NULL;
                }
                return array.array;
            }
            if (add_char(&array, buf[i]) < 0){
                return NULL;
            }
        }
    }
    if (array.size == 0) {
        free(array.array);
        return NULL;
    }
    add_char(&array, 0);

    return array.array;
}
