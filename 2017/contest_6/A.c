#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int key;
  int value;

  struct Node *left;
  struct Node *right;
} Node;


Node *new_node(int key, int value){
  Node *node = (Node *)(malloc(sizeof(Node)));

  node -> key    = key;
  node -> left   = NULL;
  node -> right  = NULL;
  node -> value  = value;

  return node;
}


Node *insert(Node *node, int key, int value){
  if(node == NULL)return new_node(key, value);

  Node *cur = node;
  Node *last;


  for(;cur != NULL;){
    last = cur;
    if(key < cur -> key){
      cur = cur -> left;
    }else if(key > cur -> key){
      cur = cur -> right;
    }else{
      cur -> value = value;
      return node;
    }
  }

  Node *an_node = new_node(key, value);

  if(key < last -> key)last -> left = an_node;
  else last -> right = an_node;

  return node;
}


Node *find_minimal(Node *cur){
  if(cur == NULL)return NULL;
  Node *node = cur;

  for(;node -> left != NULL;){

    node = node -> left;
  }

  return node;
}





Node *del(Node *node, int key){
  if(node == NULL) return NULL;
  
  Node *cur  = node; 
  Node *last = NULL;
  

  for(;cur != NULL;){
    if(key == cur -> key)break;
    
    last = cur;
    
    if(key < cur -> key)cur = cur -> left;
    else if(key > cur -> key)cur  = cur -> right;
  }

  if(cur == NULL)return node;
  
  
  Node *left = cur -> left;
  Node *right = cur -> right;
  
  if(last == NULL && (left == NULL || right == NULL)){ 
    free(cur);
    return left == NULL ? right : left;
  }

  if(left == NULL){
    if(key < last -> key) last -> left = right;
    else last -> right = right;

    free(cur);
    return node;
  }
  if(right == NULL){
    if(key < last -> key) last -> left = left;
    else last -> right = left;

    free(cur);

    return node;
  }


  Node *minimal = find_minimal(cur -> right);


  cur -> key = minimal -> key;
  cur -> value = minimal -> value;
  
  cur -> right = del (right, minimal -> key);

  return node;
}



Node *find(Node *node, int key){
  if(node == NULL)return NULL;
  if(key < node -> key)return find(node -> left, key);
  else if(key > node -> key)return find(node -> right, key);

  return node;
}
void free_tree(Node *cur){
  if(cur == NULL)return;

  free_tree(cur -> left);
  free_tree(cur -> right);
  free(cur);
}





int main(void){
  Node *tree = NULL;


  char now;

  for(;scanf("%c", &now);){
    if(now == 'F')break;
    if(now == 'A'){
      int key, value;

      if(scanf("%d %d", &key, &value) != 2)return 0;

      tree = insert(tree, key, value);
    }

    if(now == 'S'){
      int key;

      if(!scanf("%d", &key))return 0;

      Node *node = find(tree, key);

      if(node == NULL)continue;

      printf("%d %d\n", node -> key, node -> value);
    }

    if(now == 'D'){
      int key;

      if(!scanf("%d", &key))return 0;

      tree = del(tree, key);
    }
  }

  free_tree(tree);
  return 0;
}
