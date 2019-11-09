#include <stdio.h>

int func (int n, int k){
  int x1, y1;
  if (k == n + 1)return 1;

  if (scanf ("%d %d", &x1, &y1) != 2)return 0;

  if (k == n / 2)return 1;
  if (func (n, k + 1) == 0)return 0;

  int x2, y2;

  if (scanf ("%d %d", &x2, &y2) != 2)return 0;

  if (x1 == -x2 && y1 == y2)return 1;

  return 0;
}




int main(void){
  int n;

  if (!scanf ("%d", &n))return 0;
  
  int x1, y1;
  if (scanf ("%d %d", &x1, &y1) != 2)return 0;

  int some = func (n, 1);

  if (some == 0)printf ("No\n");
  else printf ("Yes\n");

  return 0;
}
