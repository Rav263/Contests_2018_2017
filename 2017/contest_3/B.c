#include <stdio.h>
#include <math.h>


typedef struct{
  double x, y;
} Point;


double mod (double a){
  return a < 0 ? -a : a;
}


double process_lenght (Point *a, Point *b){
  double x = a -> x - b -> x;
  double y = a -> y - b -> y;

  return sqrt (x * x + y * y);
}


int main(void){
  Point a, b, c;

  double x, y;
  if (scanf ("%lf %lf", &x, &y) != 2)return 0;
  a.x = x;
  a.y = y;
  if (scanf ("%lf %lf", &x, &y) != 2)return 0;
  b.x = x;
  b.y = y;
  if (scanf ("%lf %lf", &x, &y) != 2)return 0;
  c.x = x;
  c.y = y;


  double ab = process_lenght (&a, &b);
  double bc = process_lenght (&b, &c);
  double ac = process_lenght (&a, &c);

  Point ab_p, bc_p, ac_p;

  double ac_bc = ac / bc;
  double ab_ac = ab / ac;
  double ab_bc = ab / bc;

  ab_p.x = (a.x + ac_bc * b.x) / (1 + ac_bc);
  ab_p.y = (a.y + ac_bc * b.y) / (1 + ac_bc);

  bc_p.x = (b.x + ab_ac * c.x) / (1 + ab_ac);
  bc_p.y = (b.y + ab_ac * c.y) / (1 + ab_ac);

  ac_p.x = (a.x + ab_bc * c.x) / (1 + ab_bc);
  ac_p.y = (a.y + ab_bc * c.y) / (1 + ab_bc);

  printf ("%.5lf %.5lf\n", ab_p.x, ab_p.y);
  printf ("%.5lf %.5lf\n", bc_p.x, bc_p.y);
  printf ("%.5lf %.5lf\n", ac_p.x, ac_p.y);
}
