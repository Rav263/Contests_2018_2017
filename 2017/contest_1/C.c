#include <stdio.h>

int Max_int = -2147483647;

int main(void){
  int n;

  scanf ("%d", &n);

  int max1, max2 = Max_int, max3 = Max_int;

  scanf ("%d", &max1);


  for (int i = 1; i < n; i++){
    int now;

    scanf ("%d", &now);

    if (now > max1){
      max3 = max2;
      max2 = max1;
      max1 = now;
    }
    else if (now > max2){
      max3 = max2;
      max2 = now;
    }
    else if (now > max3){
      max3 = now;
    }
  }


  printf ("%d\n%d\n%d\n", max1, max2, max3);

  return 0;
}
