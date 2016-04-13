#include <stdlib.h>
#include <time.h>
#include "treap.h"

Treap_T* new_t(void* data) {
  static bool seed_rand = false;
  Treap_T* new_node;
  // Seed only once
  if (!seed_rand) {
    seed_rand = true;
    srand(time(NULL));
  }
  new_node = (Treap_T *) malloc(sizeof(Treap_T));
  new_node->priority = rand();
  new_node->data = data;
  return new_node;
}

void add_t(Treap_T* root, Treap_T* node) {
  // TODO
  return;
}

void remove_t(Treap_T* root, void* data) {
  // TODO
  return;
}

void rotate_left(Treap_T* node) {
  // If node is root return
  if (!node->parent) return;
  Treap_T * parent_node = node->parent;
  Treap_T * left_node = node->left_child;
  node->left_child = parent_node;
  parent_node->parent = node;
  parent_node->right_child = left_node;
  // Need to set parent link but might not exist
  if (left_node) {
    left_node->parent = parent_node;
  }
  return;
}

void rotate_right(Treap_T* node) {
  // If node is root return
  if (!node->parent) return;
  Treap_T * parent_node = node->parent;
  Treap_T * right_node = node->right_child;
  node->right_child = parent_node;
  parent_node->parent = node;
  parent_node->left_child = right_node;
  // Need to set parent link but might not exist
  if (right_node) {
    right_node->parent = parent_node;
  }
  return;
}
