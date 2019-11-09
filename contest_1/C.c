#include <stdio.h>
#include <stdlib.h>

//Окончательное решение задачи

enum 
{
    END_OF_RANGE = 2000,
    BEGINING_OF_RANGE = 1
};

int
main(void)
{
    int N;

    if (scanf("%d", &N) != 1) {
        return 1;
    }
   
    if (N < BEGINING_OF_RANGE || N > END_OF_RANGE) {
        return 1;
    }

    int *matrix = calloc(N * (N - 1), sizeof(*matrix));

    if (matrix == NULL) {
        return 1;
    }


    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            int now = (i * j) % N;

            matrix[now * (N - 1) + i - 1] = j; 
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            printf("%d ", matrix[i * (N - 1) + j]);
        }
        printf("\n");
    }

    free(matrix);

    return 0;
}
