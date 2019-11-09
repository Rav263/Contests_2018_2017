#include <stdio.h>


int step (int a, int b){
  int body = 1;

  for (int i = 0; i < b; i++){
    body *= a;
  }

  return body;
}

int bin_step (int a, int b, int m){
  if (b == 0) return 1;

  if (b % 2 == 1){
    return (bin_step (a, b - 1, m) * a) % m;
  }
  else{
    int x = bin_step (a, b / 2, m);
    return (x * x) % m;
  }
}



int main(void){
  int a, b, c, m;

  if (scanf ("%d %d %d %d", &a, &b, &c, &m) != 4)return 0;
  
  
  int max = 0;
  int now = 0;


  now = bin_step (a, step (b, c), m);
  if (now > max)max = now;
  now = bin_step (a, step (c, b), m);
  if (now > max)max = now;
  now = bin_step (b, step (a, c), m);
  if (now > max)max = now;
  now = bin_step (b, step (c, a), m);
  if (now > max)max = now;
  now = bin_step (c, step (a, b), m);
  if (now > max)max = now;
  now = bin_step (c, step (b, a), m);
  if (now > max)max = now;

  printf("%d\n", max);

  return 0;
}

