#include <stdio.h>
#include <ctype.h>

//Окончательное решение задачи

int
mystrspccmp(const char *str1, const char *str2)
{
    for (; 1; str1++, str2++) {
        while (isspace(*str1)) {
            str1++;
        }
        while (isspace(*str2)) {
            str2++;
        }

        if (*str1 == 0 || *str1 - *str2 != 0) {
            break;
        }
    }

    while (isspace(*str1)) {
        str1++;
    }
    while (isspace(*str2)) {
        str2++;
    }

    return (unsigned char) *str1 - (unsigned char) *str2;
}
