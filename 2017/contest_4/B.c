#include <stdio.h>
#include <string.h>


int main(void){
  int n;
  char some;
  if(!scanf("%d%c", &n, &some))return 0;
  if(some != '\n')return 0;


  char sub_string[82];

  if(!fgets(sub_string, 82, stdin))return 0;


  int len = strlen(sub_string);

  char string[len - 1];


  for(int i = 0; i < len - 1; i++){
    string[i] = sub_string[i];
  }

  n %= len - 1;


  char first_p[n];
  char second_p[len - n - 1];

  for(int i = 0; i < n; i++){first_p[i] = string[i];}
  for(int i = n; i < len - 1; i++){second_p[i - n] = string[i];}

  char sec_string[len];

  for(int i = 0; i < len - n - 1; i++){sec_string[i] = second_p[i];}
  for(int i = len - n - 1; i < len - 1; i++){sec_string[i] = first_p[i - len + n + 1];}

  sec_string[len - 1] = '\0';

  printf("%s\n", sec_string);

  return 0;
}
