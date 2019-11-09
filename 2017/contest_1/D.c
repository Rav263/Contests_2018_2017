#include <stdio.h>


int main(void){
  double x;
  int n;
  
  scanf ("%lf %d", &x, &n);

  int coof      = 1;
  int fact_body = 1;

  long double fact   = 1;
  long double step_x = x;
  long double result = 0;


  for (int i = 0; i < n; i++){
     long double now = step_x / fact;
     
     if (coof == -1)
       result -= now;
     else
       result += now;

     step_x *= x;
     step_x *= x;
     
     fact_body += 1;
     fact      *= fact_body;
     
     fact_body += 1;
     fact      *= fact_body;

     coof *= -1;
  }

  printf ("%.6Lf\n", result);

  return 0;
}
