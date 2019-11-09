#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc < 5) {
        return 1;
    }
    
    int count, hight, seed;
    int low;

    count = atoi(argv[1]);
    low = atoi(argv[2]);
    hight = atoi(argv[3]);
    seed = atoi(argv[4]);

    srand(seed);


    for (int i = 0; i < count; i++){
        int number = (rand() / (RAND_MAX + 1.0)) * (hight - low);
        number += low;


        printf("%d\n", number);
    }
}
