#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void *b){
  if(*(int *)a > *(int *)b)return  1;
  if(*(int *)a < *(int *)b)return -1;
  return 0;
}


int main(void){
  int n;

  scanf("%d", &n);

  int array[n];

  for(int i = 0; i < n; i ++){
    scanf("%d", &array[i]);
  }
  
  qsort(array, n, sizeof(int), cmp);

  if(array[0] != 1){
    printf("No\n");
    return 0;
  }

  for(int i = 0; i < n - 1; i++){
    if(array[i] + 1 != array[i + 1]){
      printf("No\n");
      return 0;
    }
  }

  printf("Yes\n");
  return 0;
}
