#include <stdio.h>

int minimal (int array[], int n){
  int min = array[0];

  for (int i = 0; i < n; i++){
    if (array[i] < min){
      min = array[i];
    }
  }

  return min;
}

int maximal (int array[], int n){
  int max = array[0];

  for (int i = 0; i < n; i++){
    if (array[i] > max){
      max = array[i];
    }
  }

  return max;
}


int main(void){
  int n;

  scanf ("%d", &n);

  int array[n];

  for (int i = 0; i < n; i++){
    scanf ("%d", &array[i]);
  }


  int min = minimal (array, n);
  int max = maximal (array, n);

  printf ("%d\n", max - min);

  return 0;
}
