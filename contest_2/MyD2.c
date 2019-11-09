#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum 
{
    INIT_SIZE = 8,
};

char * getline2(FILE *fp) {
    if (!fp) { 
        return NULL; 
    }

    size_t current_size = INIT_SIZE;
    char *res = calloc(current_size + 1, sizeof(*res));
    
    if (!res) {
        return NULL;
    }
    
    size_t ptr = 0;
    
    while (fgets(res + ptr, current_size + 1 - ptr, fp)) {
        char *found = memchr(res + ptr, 0, current_size + 1 - ptr); /* По скольку нужнен именно указатель на 
                                                                       конец считанных данных используется 
                                                                       memchr.*/
        if (found[-1] == '\n') {
            return res;
        }

        ptr += found - (res+ptr);

        current_size = 2 * current_size;

        char *new_res = realloc(res, current_size + 1);
        if (!new_res){
            free(res);
            return NULL;
        }
        res = new_res;
    }

    if (!ptr) {
        free(res);
        return NULL; 
    }

    return res;
}


