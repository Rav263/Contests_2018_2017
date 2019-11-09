#include <stdio.h>
#include <string.h>
#include <limits.h>

enum
{
    NUM_OF_BYTES = CHAR_BIT, //number of bytes in sequence
    MASK_ILON = CHAR_BIT - 1 //mask for extracting the high-order bit
};


void
print_array(unsigned char *array, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%hhx ", array[i]);
    }
}


int
main(void)
{
    unsigned char now;

    unsigned char out_array[NUM_OF_BYTES];

    memset(out_array, 0, NUM_OF_BYTES);

    int j = 0; 
    
    while (scanf("%hhx", &now) == 1) { 
        for (int i = 0; i < NUM_OF_BYTES; i++) {
            out_array[i] += (now & 1) << MASK_ILON;
            
            now >>= 1;
        }

        if (j != NUM_OF_BYTES - 1) {
            for (int i = 0; i < NUM_OF_BYTES; i++) {
                out_array[i] >>= 1;
            }
        }
        if (j == NUM_OF_BYTES - 1) {
            print_array(out_array, NUM_OF_BYTES);
            
            memset(out_array, 0, NUM_OF_BYTES);
        }
        j++;
        j %= NUM_OF_BYTES;
    }

    printf("\n");

    return 0;
}
