#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getline2(FILE *f);

int main () {
    char *some = getline2(stdin);

    if (some == NULL) {
        printf("Функция не вернула указатель на строку\n");
        return 0;
    }

    printf("Длина строки: %lu\nВы великолепны!!\n", strlen(some));

    /*for (int i = 0; i < strlen(some) + 1 ; i++){
        printf("%d ", some[i]);
    }

    printf("\n");*/
}
