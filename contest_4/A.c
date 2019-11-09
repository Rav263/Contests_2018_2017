#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int
count_octa_nums(unsigned int num)
{
    int counter = 0;
    while (num != 0) {
        num /= 8;
        counter++;
    }

    return counter;
}


void
print_string(unsigned int now, int sign_now,char *mod_string) {
    printf(mod_string, now, now, sign_now);
    printf("\n");
}

int
main(void)
{
    int n, w;
    scanf("%o %o", &n, &w);

    int max_uns = pow(2, n);

    char mod_string[100];
    int j = 0;
    int now = w;

    int size = 0;

    while (now != 0) {
        now /= 10;
        size ++;
    }


    for (int i = 0; i < 3; i++){
        mod_string[j] = '|';
        j++;
        mod_string[j] = '%';
        j++;
        sprintf(mod_string + j, "%d", w);
        j+= size;
        
        mod_string[j] = i == 0 ? 'o' : 'd';
        j++;
    }
    mod_string[j] = '|';
    mod_string[j + 1] = 0;


    for (unsigned int i = 0; i < max_uns; i++) {
        int sign_now = i > max_uns / 2 ? -1 : 1;
        sign_now *= i % (max_uns / 2);
        
        print_string(i, sign_now, mod_string);
    }
    
    return 0;
}
