void deleteNode(node **r, node *n)
{
  if (!n)
    return;

  node *son, *del_node;
  del_node = (n->left && n->right) ? succNode(n) : n;
  son = (del_node->left) ? del_node->left : del_node->right;
  if (son)
    son->parent = del_node->parent;

  if (!del_node->parent)
    *r = son;
  else
  {
    if (del_node == del_node->parent->left)
      del_node->parent->left = son;
    else
      del_node->parent->right = son;
  }

  if (del_node != n)
  {
    n->key = del_node->key;
    n->data = del_node->data;
  }
  free(del_node);
}
