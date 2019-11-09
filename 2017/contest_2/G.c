#include <stdio.h>
#include <stdlib.h>



struct Node{
  int key;
  struct Node *left;
  struct Node *right;
  int value;
  int height;
};


int max(int a, int b){
  return a > b ? a : b;
}

int height(struct Node *node){
  if(node == NULL)return 0;

  return node -> height;
}

struct Node * new_node(int key, int value){
  struct Node *node = (struct Node *)(malloc(sizeof(struct Node)));

  node -> key    = key;
  node -> left   = NULL;
  node -> right  = NULL;
  node -> value  = value;
  node -> height = 1;

  return node;
}

void calc_height(struct Node *node){
  node -> height = max(height(node -> left), height(node -> right)) + 1;
}


struct Node * left_rotate(struct Node *x){
  struct Node *y  = x -> right;
  struct Node *t2 = y ->  left;
  
  y -> left  = x;
  x -> right = t2;

  calc_height(x);
  calc_height(y);

  return y;
}


struct Node * right_rotate(struct Node *y){
  struct Node *x  = y -> left;
  struct Node *t2 = x -> right;

  x -> right = y;
  y -> left  = t2;

  calc_height(x);
  calc_height(y);

  return x;
}


int get_bal(struct Node *node){
  if(node == NULL)return 0;
  return height(node -> left) - height(node -> right);
}


struct Node * insert(struct Node *node, int key, int value){
  if(node == NULL)return new_node(key, value);

  if(key < node -> key){
    node -> left  = insert(node -> left,  key, value);
  }else{
    node -> right = insert(node -> right, key, value);
  }


  calc_height(node);

  int bal = get_bal(node);

  if(bal > 1 && key < node -> left  -> key)return right_rotate(node);
  if(bal > 1 && key > node -> left  -> key){
    node -> left = left_rotate(node -> left);
    return right_rotate(node);
  }

  if(bal < -1 && key > node -> right -> key)return left_rotate(node);
  if(bal < -1 && key < node -> right -> key){
    node -> right = right_rotate(node -> right);
    return left_rotate(node);
  }

  return node;
}


struct Node * get(struct Node *node, int key){
  if(node == NULL)return NULL;
  if(key < node -> key)return get(node -> left,  key);
  if(key > node -> key)return get(node -> right, key);

  return node;
}

void find(struct Node *node, int *a, int *b){

  if(node == NULL)return;

  if(node -> value == 1){
    if(*a != -1){
      *b = node -> key;
      return;
    }else *a = node -> key;
  }

  find(node -> left,  a, b);
  find(node -> right, a, b);
}


int main(void){
  
  struct Node *tree = NULL;

  int n;

  scanf("%d", &n);


  for(int i = 0; i < n; i++){
    int now;
    scanf("%d", &now);

    struct Node *node = get(tree, now);
    if(node == NULL)tree = insert(tree, now, 1);
    else node -> value += 1;
  }


  int a = -1;
  int b = -1;

  find(tree, &a, &b);

  if(a > b)printf("%d %d\n", b, a);
  else printf("%d %d\n", a, b);

  return 0;
}
