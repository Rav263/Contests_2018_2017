#include <stdio.h>
#include <stdlib.h>

//Окончательный вариант программы

typedef struct Pair
{
    double a;
    int b;
    int offset;
} Pair;

enum
{
    MAX_PAIRS = 16384
};




int
cmp_pairs(const void *val1, const void *val2) 
{
    if (((Pair *)val1)->a < ((Pair *)val2)->a) { 
        return -1;
    }
    
    if (((Pair *)val1)->a > ((Pair *)val2)->a) {
        return 1;
    }

    return ((Pair *)val1)->offset - ((Pair *)val2)->offset;
}

int
main(void)
{
    Pair *pair_array = calloc(MAX_PAIRS, sizeof(*pair_array));

    if (pair_array == NULL){
        return 1;
    }
    double a;
    int b;
    
    int size = 0;

    for (; scanf("%lf%d", &a, &b) == 2; size++) {
        if (size >= MAX_PAIRS) {
            free(pair_array);
            return 1;
        }

        pair_array[size].a = a;
        pair_array[size].b = b;
        pair_array[size].offset = size;
    }
    

    qsort(pair_array, size, sizeof(*pair_array), cmp_pairs);

    for (int i = 0; i < size; i++) {
        printf("%.10g %d\n", pair_array[i].a, pair_array[i].b);
    }

    free(pair_array);

    return 0;
}
