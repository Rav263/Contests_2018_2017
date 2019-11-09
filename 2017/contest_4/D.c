#include <stdio.h>
#include <string.h>


int pref_function(char *string, int n){
  int pref[n];
  pref[0] = 0;
  int j = 0;
  for(int i = 1; i < n; i++){
    for(;j > 0 && string[i] != string[j];){
      j = pref[j - 1];
    }

    if(string[i] == string[j]) j++;
    pref[i] = j;
  }

  return pref[n - 1];
}

void connect_strings(char string1[], char string2[], char string[], int n1, int n2){
  for(int i = 0; i < n1; i++){
    string[i] = string1[i];
  }
  
  string[n1]= '#';


  for(int i = 0; i < n2; i++){
    string[i + n1 + 1] = string2[i];
  }
  string[n1 + n2 + 1] = '\0';
}

int min(int a, int b){
  return a < b ? a : b;
}

int main(void){
  char sub_string1[1000002];
  char sub_string2[1000002];

  if(!fgets(sub_string1, 1000002, stdin))return 0;
  if(!fgets(sub_string2, 1000002, stdin))return 0;

  int n1 = strlen(sub_string1);
  int n2 = strlen(sub_string2);

  char string1[n1 + 1];
  char string2[n2 + 1];

  strcpy(string1, sub_string1);
  strcpy(string2, sub_string2);

  char string[n1 + n2];

  connect_strings(string1, string2, string, n1 - 1, n2 - 1);
  int res1 = pref_function(string, n1 + n2 - 1);
  if(res1 > min(n1, n2) - 1)res1 = min(n1, n2) - 1;  

  connect_strings(string2, string1, string, n2 - 1, n1 - 1);
  int res2 = pref_function(string, n1 + n2 - 1);
  if(res2 > min(n1, n2) - 1)res2 = min(n1, n2) - 1;  

  printf("%d %d \n", res1, res2);

  return 0;
}
