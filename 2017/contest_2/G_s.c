#include <stdio.h>


int main(void){
  int n;
  if (!scanf ("%d", &n))return 0;


  unsigned int array[n];

  unsigned int xsor = 0;


  for (int i = 0; i < n; i++){
    unsigned int now;

    if (!scanf ("%u", &now))return 0;
    xsor ^= now;

    array[i] = now;
  }

  unsigned int mask = 1;

  for (int i = 0; i < 32; i++){
    if (xsor & mask)break;
    mask <<= 1;
  }


  unsigned int a = 0;
  unsigned int b = 0;

  for (int i = 0; i < n; i++){
    unsigned int now = array[i] & mask;

    if (now) a = a ^ array[i];
    else     b = b ^ array[i];
  }

  if (b < a)printf ("%u %u\n", b, a);
  else printf ("%u %u\n", a, b);
}
