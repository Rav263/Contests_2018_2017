#include <stdio.h>


int main (void){
  int n, m;

  if (!scanf ("%d", &n))return 0;


  long long int array[n];

  for (int i = 0; i< n; i++){
    if (!scanf ("%lld", &array[i]))return 0;
  }

  if (!scanf ("%d", &m))return 0;

  long long int results[m];

  for (int i = 0; i < m; i++){
    long long int x_body;
    if (!scanf ("%lld", &x_body))return 0;
    long long int x = 1;

    long long int now_result = 0;
    for (int j = 0; j < n; j++){
      now_result += array[j] * x;

      x *= x_body;
    }

    results[i] = now_result;
  }


  for (int i = m - 1; i >= 0; i--){
    printf ("%lld\n", results[i]);
  }
}
