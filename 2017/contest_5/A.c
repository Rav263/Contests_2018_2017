#include <stdio.h>
#include <stdlib.h>

typedef struct Complex{
  long long int a;
  long long int b;
} Complex;


int main(void){
  int n;

  if(!scanf("%d", &n))return 0;

  Complex *array[n];

  for(int i = 0; i < n; i++){
    array[i] = malloc(n * sizeof(Complex));
  }

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      Complex now;
      if(scanf("%lld %lld", &now.a, &now.b) != 2)return 0;
      
      array[i][j] = now;
    }
  }

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      Complex now = array[j][i];
      printf("%lld %lld ", now.a, -now.b);
    }
    printf("\n");
  }

  for(int i = 0; i < n; i++){
    free(array[i]);
  }
}
