#include <stdio.h>
#include <stdlib.h>

const int BIG = 10000000;

int first     = 0;
int size      = 0;
int real_size = 10;


typedef struct Map{
  int x;
  int y;
} Map;


Map *array = NULL;


void add(Map element){
  if(size == real_size){
    real_size *= 2;
    Map * some = realloc(array, real_size * sizeof(Map));
    if(some == NULL){
      printf("WTF\n");
    }
    array = some;
  }

  array[size] = element;
  size += 1;
}


void del_first(void){
  Map err = {-1, -1};
  array[first] = err;

  first += 1;
}

void print_f(int n, int m, int field[n][m]){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      printf("%d ", field[i][j]);
    }
    printf("\n");
  }
}



int rec(int n, int m ,int field[m][n], int used[m][n]){
  if(first == size + 1)return 0;
  Map now = array[first];
  del_first();
  used[now.x][now.y] = 1;

  if(now.x + 1 <  m && !used[now.x + 1][now.y]){
    if(field[now.x + 1][now.y] > field[now.x][now.y] + 1)
      field[now.x + 1][now.y] = field[now.x][now.y] + 1;
    add((Map){now.x + 1, now.y});
  }
  
  if(now.x - 1 >= 0 && !used[now.x - 1][now.y]){
    if(field[now.x - 1][now.y] > field[now.x][now.y] + 1)
      field[now.x - 1][now.y] = field[now.x][now.y] + 1;
    add((Map){now.x - 1, now.y});
  }
  
  if(now.y + 1 <  n && !used[now.x][now.y + 1]){
    if(field[now.x][now.y + 1] > field[now.x][now.y] + 1)
      field[now.x][now.y + 1] = field[now.x][now.y] + 1;
    add((Map){now.x, now.y + 1});
  }

  if(now.y - 1 >= 0 && !used[now.x][now.y - 1]){
    if(field[now.x][now.y - 1] > field[now.x][now.y] + 1)
      field[now.x][now.y - 1] = field[now.x][now.y] + 1;
    add((Map){now.x, now.y - 1});
  }
  
 /* for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      printf("%d ", field[i][j]);
    }
    printf("\n");
  }*/



//  printf("%d %d\n", size, real_size);

  //print_f(n, m, field);
  return 1;
}


int main(void){
  int n, m, k;
  if(scanf("%d %d %d", &n, &m, &k) != 3)return 0;

  array = malloc(10 * sizeof(Map));
  
   for(int i = 0; i < k; i++){
    Map now;
    if(scanf("%d %d", &now.x, &now.y) != 2)return 0;
 
    now = (Map){now.x - 1, now.y - 1};

    add(now);
  }

  int field[m][n];
  int used[m][n];

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      field[i][j] = BIG;
      used[i][j] = 0;
    }
  }

  for(int i = first; i < size; i++){
    field[array[i].x][array[i].y] = 0;
  }

  //print_f(n, m, field);

  for(;rec(n, m, field, used););

  int max = 0;

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      if(field[i][j] > max)max = field[i][j];
    }
  }

  printf("%d\n", max);

  free(array);
  //printf("%d %d\n", size, real_size);
  return 0;
}
