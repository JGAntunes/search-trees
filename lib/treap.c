#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "treap.h"

Treap_T* new_t(void* data, int data_size) {
  static bool seed_rand = false;
  Treap_T* new_node;
  /* Seed only once */
  if (!seed_rand) {
    seed_rand = true;
    srand(time(NULL));
  }
  new_node = (Treap_T *) malloc(sizeof(Treap_T));
  new_node->priority = rand();
  new_node->position = ROOT;
  new_node->data = malloc(data_size);
  memcpy(new_node->data, data, data_size);
  return new_node;
}

void insert (Treap_T* parent, Treap_T* child, side position) {
  if (position == RIGHT) parent->right_child = child;
  if (position == LEFT) parent->left_child = child;
  child->parent = parent;
  child->position = position;
}

void add_t(Treap_T* root, void* data, int data_size, int (*compar)(const void *, const void *)) {
  Treap_T* new_node = new_t(data, data_size);
  Treap_T* current_node = root;
  Treap_T* parent_node;
  side position = ROOT;
  int diff;
  /* Binary tree insertion */
  while (current_node) {
    diff = (*compar)(new_node->data, current_node->data);
    Treap_T* temp_node;
    if (diff < 0) {
      temp_node = current_node->left_child;
      position = LEFT;
    } else {
      temp_node = current_node->right_child;
      position = LEFT;

    }
    if (!temp_node) break;
    current_node = temp_node;
  }
  insert(current_node, new_node, position);
  /* Maintain heap priority */
  /* Check if not root */
  current_node = new_node;
  parent_node = current_node->parent;
  /* Current node is not root and parent priority is bigger than child */
  while (parent_node && parent_node->priority > current_node->priority) {
    /* Check if left or right child */
    if (current_node->position == LEFT) {
      rotate_right(current_node);
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
  /* Iterate through tree items */
  while (current_node) {
    diff = (*compar)(data, current_node->data);
    if (!diff) return current_node;
    current_node = diff < 0 ? current_node->left_child : current_node->right_child;
  }
  /* Node not found */
  return NULL;
}

void remove_t(Treap_T* root, void* data, int (*compar)(const void *, const void *)) {
  Treap_T* node_remove = search_t(root, data, compar);
  Treap_T* current_node = node_remove;
  /* Node not found */
  if (!node_remove) return;
  /* Node is not a leaf */
  while (current_node->left_child || current_node->right_child) {
    if (!current_node->left_child) {
      rotate_left(current_node->right_child);
    } else if (!current_node->right_child) {
      rotate_right(current_node->left_child);
    } else if (current_node->left_child->priority < current_node->right_child->priority) {
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
  /* If node is root return */
  if (!node->parent) return;
  Treap_T * parent_node = node->parent;
  Treap_T * child_node = node->left_child;
  /* Update node links */
  node->left_child = parent_node;
  node->parent = parent_node->parent;
  node->position = parent_node->position;
  /* Update parent links */
  parent_node->parent = node;
  parent_node->right_child = child_node;
  parent_node->position = LEFT;
  /* Need to set parent link on new right child but might not exist */
  if (child_node) {
    child_node->parent = parent_node;
    child_node->position = RIGHT;
  }
  /* Need to set child link on parent but might not exist */
  if (node->parent) {
    if(node->position == LEFT) node->parent->left_child = node;
    else node->parent->right_child = node;
  }
  return;
}

void rotate_right(Treap_T* node) {
  /* If node is root return */
  if (!node->parent) return;
  Treap_T * parent_node = node->parent;
  Treap_T * child_node = node->right_child;
  /* Update node links */
  node->right_child = parent_node;
  node->parent = parent_node->parent;
  node->position = parent_node->position;
  /* Update parent links */
  parent_node->parent = node;
  parent_node->left_child = child_node;
  parent_node->position = RIGHT;
  /* Need to set parent link but might not exist */
  if (child_node) {
    child_node->parent = parent_node;
    child_node->position = LEFT;
  }
  /* Need to set child link on parent but might not exist */
  if (node->parent) {
    if(node->position == LEFT) node->parent->left_child = node;
    else node->parent->right_child = node;
  }
  return;
}
