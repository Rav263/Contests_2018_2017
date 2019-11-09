#include <stdio.h>

void generate (int from, int to, int lenght, int posl[], int index){
  if(lenght == 0){
    for(int i = 0; i < index; i++){
      printf ("%d ", posl[i]);
    }
    printf ("\n");
    return;
  }
  for (int i = from; i < to; i++){
    posl[index] = i;
    generate (i + 1, to, lenght - 1, posl, index + 1);
  }
}


int main(void){
  int n, k;

  if (scanf ("%d %d", &n, &k) != 2)return 0;

  int posl[k];
  generate (0, n, k, posl, 0);


  return 0;
}
