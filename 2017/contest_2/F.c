#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int size;
  int array[];
}Array;

int cmp (const void *a, const void *b){
  if (*(int *)a > *(int *)b)return  1;
  if (*(int *)a < *(int *)b)return -1;
  return 0;
}

void swap (int *a, int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

Array * roll_up_arr (int array[], int *counter){
  int an_array[8];
  int index = 0;

  for (int i = 0; i < 7; i++){
    if (array[i] != array[i + 1]){
      an_array[index] = array[i];
      index++;
      continue;
    }
    an_array[index] = array[i];
    index++;

    for(int j = i + 1; ; j++){
      if(array[i] != array[j])break;
      *counter += array[i];
      i++;
    }
  }


  Array *ans = (Array *)malloc(sizeof(int) + sizeof(int[index]));
  
  for(int i = 0; i < index; i++){
    ans -> array[i] = an_array[i];
  }

  ans -> size  = index;

  return ans;
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
  }

  Array *front = roll_up_arr (front_s, &counter);
  printf("%d\n", counter);
}
