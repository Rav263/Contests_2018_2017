#include <stdio.h>


int main(void){
  int array_sub[10000];

  int a;
  int n = 0;

  for (;scanf ("%d", &a);n++){
    if (a == 0)break;
    array_sub[n] = a;
  }

  int array[n];
  for (int i = 0; i < n; i++){
    array[i] = array_sub[i];
  }

  for (int i = 0; i < n; i += 2){
    printf ("%d ", array[i]);
  }

  for (int i = (n % 2 == 1 ? n - 2 : n - 1); i >= 0; i -= 2){
    printf ("%d ", array[i]);
  }
  printf ("\n");
  
  return 0;
}
