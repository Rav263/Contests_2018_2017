#include <stdio.h>
#include <math.h>


typedef struct{
  float x, y, z, r;
} sphere;


void print_sphere (sphere a){
  printf ("%lf %lf %lf %lf\n", a.x, a.y, a.z, a.r);
}

void swap (sphere *a, sphere *b){
  sphere temp = *a;
  *a = *b;
  *b = temp;
}


int is_point (sphere a, sphere b){
  float x = a.x - b.x;
  float y = a.y - b.y;
  float z = a.z - b.z;
  float r = a.r + b.r;

  double l = x * x + y * y + z * z;

  if (b.r < a.r)swap (&a, &b);
  
  if (sqrt(l) + a.r < b.r)return 0;

  if (l  <= r * r)return 1;
  
  return 0;
}

int main(void){
  int n;

  scanf ("%d", &n);

  sphere spheres[n];

  for (int i = 0; i < n; i++){
    float x, y, z, r;
    scanf ("%f %f %f %f", &x, &y, &z, &r);

    spheres[i].x = x;
    spheres[i].y = y;
    spheres[i].z = z;
    spheres[i].r = r;
  }


  for (int i = 0; i < n - 1; i++){
    for (int j = i + 1; j < n; j++){
      if (is_point(spheres[i], spheres[j])){
        printf ("YES\n");
        
        return 0;
      }
    }
  }
 
  printf ("NO\n");

  return 0;
}
