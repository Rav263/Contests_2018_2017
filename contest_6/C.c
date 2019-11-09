#include <string.h>

const char string[] = "rwxrwxrwx";

enum 
{
    STRING_SIZE = sizeof(string),
};



int
parse_rwx_permissions(const char *str)
{
    if (str == NULL) { 
        return -1;
    }
    long size = strlen(str);

    if (size != STRING_SIZE - 1) {
        return -1;
    }

    int result = 0;

    for (int i = 0; i < size; i++) {
        result <<= 1;

        result += str[i] == string[i];

        if ((result & 1) == 0 && str[i] != '-') {
            return -1;

        }
    }

    return result;
}
