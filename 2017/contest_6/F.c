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

void free_list(List *node){
  if(node == NULL)return;

  free_list(node -> next);

  free(node);
}

List *sort(List *start, List *end, int size){
  if(size == 1)return start;

  List *an_start = start;

  for(int i = 0; i < size / 2; i++){
    an_start = an_start -> next;
  }

  int size_f = size / 2;
  int size_s = size % 2 == 1 ? size / 2 + 1 :  size / 2;
  
  List *first  = sort(start, an_start, size_f);
  List *second = sort(an_start -> next, end, size_s);

  List *now1

  for(int i = 0; i < size_f; i++){
    
  }


}


int main(void){
  FILE *f = fopen("input.txt", "r");  
  
  List *root = NULL;
  int size = 0;


  for(int i = 0;; i++){
    int now;
    if(!fscanf(f, "%d", &now)){
      size = i;
      return 0;
    }
    
    root = push_back(root, now);
  }

  fclose(f);



  free_list(root);

  return 0;
}
