#include <stdio.h>
#include <stdlib.h>

int cmp (const void *a, const void *b){
  if (*(int *)a > *(int *)b)return  1;
  if (*(int *)a < *(int *)b)return -1;
  return 0;
}



int main (void){
  int front_s[8];
  int right_s[8];

  for (int i = 0; i < 8; i++){
    if (!scanf ("%d", &front_s[i]))return 0;
  }

  for (int i = 0; i < 8; i++){
    if (!scanf ("%d", &right_s[i]))return 0;
  }

  int counter = 0;


  qsort (front_s, 8, sizeof(int), cmp);
  qsort (right_s, 8, sizeof(int), cmp);

  if (front_s[7] != right_s[7]){
    printf ("-1\n");
    return 0;
  }


  for (int i = 0; i < 8; i++){
    counter += front_s[i];
    
    for (int j = 0; j < 8; j ++){
      if (front_s[i] == right_s[j]){
        right_s[j] = 0;
        break;
      }
    }
  }


  for(int i = 0; i < 8; i++){
    counter += right_s[i];
  }

  printf("%d\n", counter);
}
