#include <stdio.h>
#include <stdlib.h>

enum 
{
    A = 1103515245,
    C = 12345,
    M = 2147483648,
};

typedef struct RandomGenerator RandomGenerator;

typedef struct RandomOperations
{
    unsigned int (*next)(RandomGenerator *);
    void (*destroy)(RandomGenerator *);
} RandomOperations;


typedef struct RandomGenerator
{
    unsigned int now;
    RandomOperations *ops;
} RandomGenerator;


unsigned int next(RandomGenerator *rr) {
    rr->now = (A * rr->now + C) % M;
    return rr->now;
}

void destroy(RandomGenerator *rr) {
    free(rr);
}

RandomOperations ops = {next, destroy};

RandomGenerator *random_create(int seed) {
    RandomGenerator *rr = calloc(1, sizeof(*rr));
    rr->now = seed;
    rr->ops = &ops;
    return rr;
}


