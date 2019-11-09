#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

void
print_string(int32_t  now, int32_t sign_now, int w) {
    printf("|%*o|%*d|%*d|\n", w, now, w, now, w, sign_now);
}

int
main(void)
{
    int n, w;
    if (scanf("%o%o", &n, &w) != 2) {
        return 1;
    }

    uint32_t max_uns = 1;
    max_uns <<= n;

    for (uint32_t i = 0; i < max_uns; i++) {
        int32_t sign_now = i > max_uns / 2 ? -1 : 1;
        sign_now *= i % (max_uns / 2);
        
        print_string(i, sign_now, w);
    }
    
    return 0;
}
