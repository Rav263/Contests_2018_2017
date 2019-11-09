#include <stdio.h>

typedef struct {
  int x, y;
} coord;


int generate_values (int a11, int a12, int a21, int a22, int b1, int b2, coord coords[]){
  if (b1 == 1){
    if (a11 == 0 && a12 == 0){
      return -1;
    }
    if (a11 == 0 && a12 == 1){
      coord now0  = {0, 1};
      coords[1]  = now0;
      coord now1 = {1, 1};
      coords[3]  = now1;
    }
    if (a11 == 1 && a12 == 0){
      coord now0  = {1, 0};
      coords[2]  = now0;
      coord now1 = {1, 1};
      coords[3]  = now1;
    }
    if (a11 == 1 && a12 == 1){
      coord now0 = {1, 0};
      coords[2]  = now0;
      coord now1 = {0, 1};
      coords[1]  = now1;
    }
  }
  else{
    if (a11 == 0 && a12 == 1){
      coord now0 = {1, 0};
      coords[2]  = now0;
      coord now1 = {0, 0};
      coords[0]  = now1;
    }
    if (a11 == 1 && a12 == 0){
      coord now0 = {0, 1};
      coords[1]  = now0;
      coord now1 = {0, 0};
      coords[0]  = now1;
    }
    if (a11 == 1 && a12 == 1){
      coord now0 = {1, 1};
      coords[3]  = now0;
      coord now1 = {0, 0};
      coords[0]  = now1;
    }
    if (a11 == 0 && a12 == 0){
      coord now0 = {0, 0};
      coord now1 = {0, 1};
      coord now2 = {1, 0};
      coord now3 = {1, 1};
      
      coords[0] = now0;
      coords[1] = now1;
      coords[2] = now2;
      coords[3] = now3;
    }
  }

  coord err = {-1, -1};

  if (b2 == 1){
    if (a21 == 0 && a22 == 0){
      return -1;
    }
    if (a21 == 0 && a22 == 1){
      if (coords[1].y == -1 && coords[3].x == -1)return -1;
      
      coords[2] = err;
      coords[0] = err;
    }
    if (a21 == 1 && a22 == 0){
      if (coords[2].x == -1 && coords[3].x == -1)return -1;
      
      coords[1] = err;
      coords[0] = err;
    }
    if (a21 == 1 && a22 == 1){
      if (coords[1].x == -1 && coords[2].y == -1)return -1;
      
      coords[0] = err;
      coords[3] = err;
    }
  }
  else{
    if (a21 == 0 && a22 == 1){
      if (coords[0].y == -1 && coords[2].y == -1)return -1;
      
      coords[1] = err;
      coords[3] = err;
    }
    if (a21 == 1 && a22 == 0){
      if (coords[0].x == -1 && coords[1].x == -1)return -1;
      
      coords[2] = err;
      coords[3] = err;
    }
    if (a21 == 1 && a22 == 1){
      if (coords[0].x == -1 && coords[3].x == -1)return -1;
     
      coords[1] = err;
      coords[2] = err;
    }
  }
  return 0;
}

void print (int x[], int y[]){
  unsigned int xx = 0;
  unsigned int yy = 0;

  for (int i = 31; i > 0; i--){
    xx += x[i];
    yy += y[i];

    xx *= 2;
    yy *= 2;
  }

  xx += x[0];
  yy += y[0];


  printf ("Yes\n%u %u\n", xx, yy);
}

void print_values (coord values[]){
  for (int i = 0; i < 4; i ++){
    printf ("%d: %d %d\n", i, values[i].x, values[i].y);
  }

}

int some_function (unsigned int a11, unsigned int a12, 
                  unsigned int a21, unsigned int a22,
                  unsigned int b1 , unsigned int b2){
 
  
  int x[32];
  int y[32];


  for (int i = 0; i < 32; i++){
    coord values[] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};

    int some = generate_values (a11 % 2, a12 % 2, a21 % 2, a22 % 2, b1 % 2, b2 % 2, values);
    if (some == -1)return -1;
    
    for (int j = 0; j < 4; j++){
      if (values[j].x != -1){
        x[i] = values[j].x;
        y[i] = values[j].y;
        break;
      }
    }

    a11 /= 2;
    a12 /= 2;
    a21 /= 2;
    a22 /= 2;
    b1  /= 2;
    b2  /= 2;
  }

  print (x, y);
  return 0;
}




int main(void){
  unsigned int a11, a12, a21, a22, b1, b2;


  scanf ("%u %u %u %u %u %u", &a11, &a12, &a21, &a22, &b1, &b2);

  int some = some_function (a11, a12, a21, a22, b1, b2);


  if (some == -1)printf ("No\n");

  return 0;
}
