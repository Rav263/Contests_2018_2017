#include <stdio.h>
#include <stdlib.h>

typedef struct Map{
  int x;
  int y;
} Map;



int mod(int a){
  return a < 0 ? -a : a;
}


void count(int m, int n, int field[m][n], Map now){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      int temp = mod(i - now.x) + mod(j - now.y);

      if(temp < field[i][j])field[i][j] = temp;
    }
  }
}



int main(void){
  int n, m, k;

  if(scanf("%d %d %d", &n, &m, &k) != 3)return 0;

  Map array[11];

  for(int i = 0; i < k; i++){
    Map now;
    if(scanf("%d %d", &now.x, &now.y) != 2)return 0;
 
    now = (Map){now.x - 1, now.y - 1};

    array[i] = now;
  }

  int field[m][n];

  for(int x = 0; x < m; x++){
    for(int y = 0; y < n; y++){
      field[x][y] = 100000000;
    }
  }

  for(int i = 0; i < k; i++){
    count(m, n, field, array[i]);
  }


  int max = 0;

  for(int x = 0; x < m; x++){
    for(int y = 0; y < n; y++){
      if(field[x][y] > max)max = field[x][y];
    }
  }

  printf("%d\n", max);

  return 0;
}
