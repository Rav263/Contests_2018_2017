#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
    int a = R_OK;
    int b = W_OK;
    int c = X_OK;


    printf("%x %x %x\n", a, b, c);

    char string[100];

    for(int i = 0; scanf("%s", string); i++){
        struct stat stb = {};

        stat(string, &stb);

        int is = access(string, X_OK);
        
        printf("%d %d %o %d\n", stb.st_uid, stb.st_gid, stb.st_mode, is);
    }
}

