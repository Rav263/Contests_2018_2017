#include <stdio.h>
#include <inttypes.h>



int main(void){
  uint32_t n, k;

  scanf ("%d %d", &n, &k);

  uint32_t a = n >> k;
  uint32_t b = n << (32 - k);
  uint32_t c = a | b;

  printf ("%d", c);
}
