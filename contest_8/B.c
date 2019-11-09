#include <stdio.h>
#include <stdlib.h>

enum 
{
    MAX_PER = 100,
};

typedef struct Pair
{
    int value;
    int freq;
} Pair;


int main(void) {
    int n, m;
    unsigned seed;
    scanf("%d", &n);
    Pair *pairs = calloc(n, sizeof(*pairs));
    

    for (int i = 0; i < n ; i++) {
        scanf("%d%d", &pairs[i].value, &pairs[i].freq);
    }
    int freqs[MAX_PER + 1] = {};
    int now_index = 0;
    int now_freq = pairs[0].freq;

    for (int i = 0; i < MAX_PER; i++) {
        if (i == now_freq) {
            now_index += 1;
            now_freq += pairs[now_index].freq;
        }
        freqs[i] = pairs[now_index].value;
        if (i == MAX_PER) freqs[i] = pairs[now_index - 1].value;
    }

    scanf("%d%u", &m, &seed);

    srand(seed);
    for (int i = 0; i < m; i++) {
        int now = (rand() / (RAND_MAX + 1.0)) * MAX_PER;
        printf("%d\n", freqs[now]);
    }

    free(pairs);
    return 0;
}
