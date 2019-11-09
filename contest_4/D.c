#include <stdlib.h>


void
normalize_path(char *buf)
{
    char *now_ptr = buf;
    char *end_ptr = buf;

    while (*end_ptr != 0) {
        if (*end_ptr == '/') {
            *now_ptr = '/';
            now_ptr++;
        }
        while (*end_ptr == '/') {
            end_ptr++;
        }

        if (*end_ptr == 0) {
            break;
        }

        *now_ptr = *end_ptr;
        now_ptr++;
        end_ptr++;
    }
    *now_ptr = 0;
}
