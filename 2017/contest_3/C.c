#include <stdio.h>

int func (int index, int array[], int n, int sum1, int sum2){
  if(index == n){
    if(sum1 == sum2)return sum1;
    return 0;
  }


  int max = 0;
  int now = func (index + 1, array, n, sum1 + array[index], sum2);
  if (now > max)max = now;
  now     = func (index + 1, array, n, sum1, array[index] + sum2);
  if (now > max)max = now;
  now     = func (index + 1, array, n, sum1, sum2);
  if (now > max)max = now;

  return max;
}




int main(void){
  int n;
  if (!scanf ("%d", &n))return 0;

  int array[n];

  for (int i = 0; i < n; i ++){
    if (!scanf ("%d", &array[i])) return 0;
  }

  printf ("%d\n", func (0, array, n, 0, 0));
  
  return 0;
}
