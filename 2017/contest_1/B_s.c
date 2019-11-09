#include <stdio.h>


int main(void){
  unsigned int n, k;

  scanf("%u %u", &n, &k);

  unsigned int a = (n >> k) | (n << (32 - k));


  printf("%u", a);

  return 0;
}
