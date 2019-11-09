#include <stdio.h>
#include <stdlib.h>


typedef struct Array{
  int size;
  int real_size;
  int first;
  int *array;
} Array;



void add(Array *arr, int now){
  if(arr -> size == arr -> real_size - 1){
    arr -> real_size *= 2;
    int * some = realloc((arr -> array), arr -> real_size * sizeof(int));
    if(some == NULL){
      return;
    }

    (arr -> array) = some;
  }

  arr -> array[arr -> size] = now;
  arr -> size += 1;
}

int get(Array *arr, int index){
  return arr->array[index];
}

int main(void){
  FILE *f = fopen("input.bin", "rb");

  Array ar;
  ar.size = 0;
  ar.real_size = 10;
  ar.first = 0;
  ar.array = malloc(10 * sizeof(int));

  if(ar.array == NULL)return 0;

  Array *arr = &ar;

  for(;;){
    int now;
    if(!fread(&now, sizeof(int), 1, f))break;
    add(arr, now);
  }

  fclose(f);

  int some = 0;

  for(int i = 0; i < arr -> size; i++){
    if(i == arr -> size - 1){
      some = -1;
      break;
    }else{
      if((2 * i + 1 < arr -> size && get(arr, i) < get(arr, i * 2 + 1)) ||
         (2 * i + 2 < arr -> size && get(arr, i) < get(arr, i * 2 + 2)))break;
    }
  }
  for(int i = 0; i < arr -> size; i++){
    if(i == arr -> size - 1){
      some = 1;
      break;
    }else{
      if((2 * i + 1 < arr -> size && get(arr, i) > get(arr, i * 2 + 1)) ||
         (2 * i + 2 < arr -> size && get(arr, i) > get(arr, i * 2 + 2)))break;
    }
  }

  f = fopen("output.bin", "wb");
  
  fwrite(&some, sizeof(int), 1, f);
  fclose(f);
  free(arr -> array);


  return 0;
}
