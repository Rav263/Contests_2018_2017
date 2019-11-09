#include <stdio.h>

long long int MAX =  9223372036854775807;
long long int MIN = -9223372036854775807;


int main(void){
  int n;
  scanf ("%d", &n);

  long long int max1 = MIN, max2 = MIN;
  long long int min1 = MAX, min2 = MAX;

  for (int i = 0; i < n; i++){
    long long int now;

    scanf ("%lld", &now);

    if (now >= max2){
      if (now > max1){
        max2 = max1;
        max1 = now;
      }
      else
        max2 = now;
    }
    if (now <= min2){
      if (now < min1){
        min2 = min1;
        min1 = now;
      }
      else
        min2 = now;
    }
  }


  if (min1 * min2 >= max1 * max2){
    printf ("%lld %lld\n", min1, min2);
  }
  else{
    printf ("%lld %lld\n", max2, max1);
  }

  return 0;
}
