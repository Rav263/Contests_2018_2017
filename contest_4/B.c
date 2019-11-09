#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char mod_string[] = "xwrxwrxwr";


enum 
{
    OCTAL_SYSTEM = 8,
    STRING_SIZE = sizeof(mod_string) - 1
};




void
print(long now)
{
    char string[STRING_SIZE + 1];


    for (int i = 0; i < STRING_SIZE; i++) {
        if ((now & 1) == 1) {
            string[STRING_SIZE - i - 1] = mod_string[i];
        } else {
            string[STRING_SIZE - i - 1] = '-';
        }
        now >>= 1;
    }
    string[STRING_SIZE] = 0;

    printf("%s\n", string);
}

int
main(int argc, char *argv[])
{
    char *some_ptr = NULL;

    for (int i = 1; i < argc; i++) {
        long some = strtol(argv[i], &some_ptr, OCTAL_SYSTEM);

        print(some);
    }

    return 0;
}

