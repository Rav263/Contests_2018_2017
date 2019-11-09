#include <stdio.h>
#include <stdlib.h>

typedef struct List{
  int data;
  struct List *next;
} List;


void print_list(List *node, FILE *f){
  if(node == NULL)return;

  fprintf(f, "%d ", node -> data);
  print_list(node -> next, f);
}

List *new_node(int data){
  List *node = (List*) malloc(sizeof(List));

  node -> data = data;

  return node;
}


List *push_back(List *node, int data){
  if(node == NULL)return new_node(data);

  List *root = node;

  for(;node -> next != NULL;){
    node = node -> next;
  }

  node -> next = new_node(data);

  return root;
}


List *rem(List *node, int data, int *flg){
  if(node == NULL){
    *flg = 0;
    return NULL;
  }
  if(node -> data == data){
    *flg = 1;
    List *tmp = node -> next;
    free(node);
    return tmp;
  }

  List *root = node;
  List *last = NULL;

  for(;node != NULL && node -> data != data;){
    last = node;
    node = node -> next;
  }

  if(node == NULL){
    *flg = 0;
    return root;
  }

  last -> next = node -> next;
  *flg = 1;

  free(node);

  return root;
}

List *get_first(List *root, int *data){
  if(root == NULL)return NULL;

  List *tmp = root -> next;

  *data = root -> data;

  free(root);

  return tmp;
}

void free_list(List *node){
  if(node == NULL)return;

  free_list(node -> next);

  free(node);
}

int main(void){
  FILE *f = fopen("input.txt", "r");  


  List *f_root = NULL;
  List *s_root = NULL;

  for(;;){
    int now;
    if(!fscanf(f, "%d", &now))return 0;
    
    if(now == -1)break;
    f_root = push_back(f_root, now);
  }


  for(;;){
    int now;
    if(!fscanf(f, "%d", &now))return 0;

    if(now == -1)break;
    s_root = push_back(s_root, now);
  }
  fclose(f);

  f = fopen("output.txt", "w");

  int data = 0;


  for(;;){
    int flg = 1;
    s_root = get_first(s_root, &data);
    for(;flg;)f_root = rem(f_root, data, &flg);
    
    if(s_root == NULL)break;
  }

  print_list(f_root, f);
  fprintf(f, "\n");
  fclose(f);

  free_list(f_root);

  return 0;
}
