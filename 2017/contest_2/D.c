#include <stdio.h>


int main (void){
  int n;

  if(!scanf ("%d", &n))return 0;

  int array[n];

  for (int i = 0; i < n; i++){
    int now;

    if(!scanf ("%d", &now))return 0;

    array[i] = now;
  }

  int counter = 0;


  for (int i = 0; i < n - 2; i++){
    for (int j = i + 2; j < n; j++){
      if(i % 2 != j % 2)continue;
      int k = (i + j) / 2;
    
      if (array[i] % 2 != array[j] % 2)continue;
      if ((array[i] + array[j]) / 2 == array[k])counter++;
    }
  }

  printf ("%d\n", counter);

  return 0;
}
