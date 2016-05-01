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

void insert_left (Treap_T* parent, Treap_T* child) {
  parent->left_child = child;
  child->parent = parent;
}

void insert_right (Treap_T* parent, Treap_T* child) {
  parent->right_child = child;
  child->parent = parent;
}

void add_t(Treap_T* root, void* data, int (*compar)(const void *, const void *)) {
  Treap_T* new_node = new_t(data);
  Treap_T* current_node = root;
  Treap_T* parent_node;
  int diff;
  // Binary tree insertion
  while (current_node) {
    diff = (*compar)(new_node->data, current_node->data);
    Treap_T* temp_node;
    if (diff < 0) {
      temp_node = current_node->left_child;
      if (!temp_node) insert_left(current_node, new_node);
    } else {
      temp_node = current_node->right_child;
      if (!temp_node) insert_right(current_node, new_node);
    }
    current_node = temp_node;
  }
  // Maintain heap priority
  // Check if not root
  current_node = new_node;
  parent_node = current_node->parent;
  // Current node is not root and parent priority is bigger than child
  while (parent_node && parent_node->priority > current_node->priority) {
    // Check if left or right child
    if (parent_node->left_child) {
      diff = (*compar)(parent_node->left_child->data, current_node->data);
      if (!diff) {
        rotate_right(current_node);
      } else {
        rotate_left(current_node);
      }
    } else {
      rotate_left(current_node);
    }
    parent_node = current_node->parent;
  }
  return;
}

Treap_T* search_t(Treap_T* root, void* data, int (*compar)(const void *, const void *)) {
  Treap_T* current_node = root;
  int diff;
  // Iterate through tree items
  while (current_node) {
    diff = (*compar)(data, current_node->data);
    if (!diff) return current_node;
    current_node = diff < 0 ? current_node->left_child : current_node->right_child;
  }
  // Node not found
  return NULL;
}

void remove_t(Treap_T* root, void* data, int (*compar)(const void *, const void *)) {
  Treap_T* node_remove = search_t(root, data, compar);
  Treap_T* current_node = node_remove;
  // Node not found
  if (!node_remove) return;
  // Node is not a leaf
  while (current_node->left_child || current_node->right_child) {
    if (!current_node->left_child) rotate_left(current_node->right_child);
    if (!current_node->right_child) rotate_right(current_node->left_child);
    if (current_node->left_child->priority < current_node->right_child->priority) {
      rotate_right(current_node->left_child);
    } else {
      rotate_left(current_node->right_child);
    }
  }
  free(node_remove->data);
  free(node_remove);
  return;
}

void rotate_left(Treap_T* node) {
  // If node is root return
  if (!node->parent) return;
  Treap_T * parent_node = node->parent;
  Treap_T * left_node = node->left_child;
  node->left_child = parent_node;
  node->parent = parent_node->parent;
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
  node->parent = parent_node->parent;
  parent_node->parent = node;
  parent_node->left_child = right_node;
  // Need to set parent link but might not exist
  if (right_node) {
    right_node->parent = parent_node;
  }
  return;
}
