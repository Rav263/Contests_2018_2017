#include <stdio.h>
#include <math.h>


float min (float a, float b){
  return a < b ? a : b;
}
float max (float a, float b){
  return a > b ? a : b;
}

void swap (float *a, float *b){
  float temp = *a;
  *a = *b;
  *b = temp;
}

int main(void){
  float a, b, c, d;

  scanf ("%f %f %f %f", &a, &b, &c, &d);

  if (a > b)swap (&a, &b);
  if (c > d)swap (&c, &d);

  if (a < c){
    printf("NO\n");
    return 0;
  }
  if (b >= c && b >= d){
    printf("YES\n");
    return 0;
  }


  double r = (double)(c * c + d * d) / 4;
 
  
  if (r * 4 > a * a + b * b){
    printf("NO\n");
    return 0;
  }
  if (r <= b * b / 4){
    printf("YES\n");
    return 0;
  }

  double x = sqrt (r - a * a / 4);
  double y = sqrt (r - b * b / 4);

  double l = (b / 2 - x) * (b / 2 - x) +
             (a / 2 - y) * (a / 2 - y);

  if(l >= c * c){
    printf ("YES\n");
  }
  else{
    printf ("NO\n");
  }

  return 0;
}
