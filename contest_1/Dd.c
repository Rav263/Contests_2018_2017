#include <stdio.h>
#include <ctype.h>

int
mystrspccmp(const char *, const char *);


int
main(void) 
{
    char a[100] = "аа ааб";
    char b[100] = "аа ааа";

    printf("%d\n", mystrspccmp(a, b)); 

    return 0;
}
