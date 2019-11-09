#include <stdio.h>

typedef struct{
  int x;
  int y;
}Point;

int mod (int a){
  return a < 0 ? -a : a;
}


void get_turn (Point *turn){
  char x, y, prob;

  if (!scanf ("%c", &x))return;
  if (x == 'X'){
    turn -> x = -1;
    turn -> y = -1;
    return;
  }
  if (!scanf ("%c", &y))return;
  if (!scanf ("%c", &prob))return;
  if (prob != '\n')return;

  int a = x - 'A';
  int b = y - '1';

  turn -> x = b;
  turn -> y = a;
}


int check_turn_fer (Point last_turn, Point turn){
  int x = mod (last_turn.x - turn.x);
  int y = mod (last_turn.y - turn.y);

  if(x == 0 && y == 0)return 0;
  if(x == y)return 1;
  if(x == 0 || y == 0)return 1;

  return 0;
}

int check_turn_kon (Point last_turn, Point turn){
  int x = mod (last_turn.x - turn.x);
  int y = mod (last_turn.y - turn.y);

  if (x == 1 && y == 2)return 1;
  if (x == 2 && y == 1)return 1;

  return 0;
}


int main(void){
  Point last_turn = {0, 0};

  int i = 0;

  for (i = 0;; i++){
    Point turn;
    get_turn (&turn);

    if (turn.x == -1)break;

    if (last_turn.x == 7 && last_turn.y == 7){
      printf ("Cheaters\n");
      return 0;
    }

    if (i % 2 == 0){
      int ch = check_turn_kon (last_turn, turn);
      
      if (ch == 0){
        printf ("Cheaters\n");
        return 0;
      }
    }else{
      int ch = check_turn_fer (last_turn, turn);
      
      if (ch == 0){
        printf ("Cheaters\n");
        return 0;
      }
    }

    
    last_turn.x = turn.x;
    last_turn.y = turn.y;
    turn.x = 0;
    turn.y = 0;
    
  }
  if (last_turn.x != 7 || last_turn.y != 7){
    printf ("Cheaters\n");
    return 0;
  }

  if (i % 2 == 0){
    printf ("Tolik\n");
  }
  else{
    printf ("Garik\n");
  }
}
