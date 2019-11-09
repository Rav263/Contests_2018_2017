#include <stdio.h>
#include <math.h>


int isprime (int a){
  if (a < 2)return 0;
  
  for (int i = 2; i <= sqrt (a); i++){
    if (a % i == 0)return 0;
  }
  return 1;
}



int main(void){
  int n;
  if (!scanf ("%d", &n))return 0;

  for (int i = n;; i++){
    if (isprime (i) == 1){
      printf ("%d\n", i);
      break;
    }
  }

  return 0;
}
