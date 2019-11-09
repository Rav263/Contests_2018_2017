#include <stdio.h>
#include <stdlib.h>

union Num{
  int  a;
  char b[4];
};

union Short{
  short a;
  char b[2];
};

union Long{
  long long int a;
  char b[8];
};


int main(void){
  FILE *f = fopen("matrix.in", "rb");

  union Short N;
  
  if(!fread(&N.b[1], sizeof(char), 1, f))return 0;
  if(!fread(&N.b[0], sizeof(char), 1, f))return 0;

  short n = N.a;
  if(n == 0){
    fclose(f);

    f = fopen("output.bin", "wb");

    union Long some;
    some.a = 0;

    fwrite(some.b, sizeof(char), 8, f);
    fclose(f);

    return 0;
  }

  int matrix[n * n];

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      union Num some;
      for(int k = 3; k >= 0; k--){
        if(!fread(&some.b[k], sizeof(char), 1, f))break;
      }
      matrix[i * n + j] = some.a;
    }
  }
  fclose(f);

  long long int sum = 0;

  for(int i = 0; i < n; i++)sum += matrix[i * n + i];
  union Long some;
  some.a = sum;

  f = fopen("trace.out", "wb");
  for(int i = 7; i >= 0; i--){
    fwrite(&some.b[i], sizeof(char), 1, f);
  }
  fclose(f);

  return 0;
}
