#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_cmp(char *a, char *b){
  for(int i = 0;; i++){
    if(a[i] == '\0' && b[i] == '\0')return 0;
    if(a[i] == '\0' && b[i] != '\0')return -1;
    if(a[i] != '\0' && b[i] == '\0')return 1;

    if(a[i] == b[i])continue;
    if((a[i] >= 'a' && a[i] <= 'z') && (b[i] >= 'A' && b[i] <= 'Z'))return -1;
    if((a[i] >= 'A' && a[i] <= 'Z') && (b[i] >= 'a' && b[i] <= 'z'))return 1;
    return a[i] - b[i];
  }
  return 0;
}


int cmp(const void *a, const void *b){
  char *aa = *(char **)a;
  char *bb = *(char **)b;

  return string_cmp(aa, bb);
}


int main(void){
  int n;
  
  if(scanf("%d", &n) != 1)return 0;

  int len = 9000000 / n + 5;

  char *array[n];

  for(int i = 0; i < n; i ++){
    array[i] = malloc(len * sizeof(char));
    
    if(!scanf("%s", array[i])){
      return 0;
    }
  }

  qsort(array, n, sizeof(char *), cmp);

  for(int i = 0; i < n; i++){
    printf("%s\n", array[i]);
  }

  for(int i = 0; i < n; i++){
    free(array[i]);
  }

  return 0;
}
