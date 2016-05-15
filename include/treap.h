#ifndef TREAP_H
#define TREAP_H

typedef enum { ROOT, LEFT, RIGHT } side;

typedef struct Treap_T{
    int priority;
    void* data;
    void* key;
    side position;
    struct Treap_T* parent;
    struct Treap_T* left_child;
    struct Treap_T* right_child;
} Treap_T;

typedef enum { false, true } bool;

Treap_T** new_treap();

Treap_T* new_t(void* key, void* data, int key_size, int data_size);

Treap_T* add_t(Treap_T** root, Treap_T* new_node, int (*compar)(const void *, const void *));

void remove_t(Treap_T** root, void* key, int (*compar)(const void *, const void *));

Treap_T* search_t(Treap_T** root, void* key, int (*compar)(const void *, const void *));

Treap_T* search_add_t(Treap_T** root, void* key, void* data, int key_size,
  int data_size, int (*compar)(const void *, const void *));

void rotate_left(Treap_T** root, Treap_T* parent);

void rotate_right(Treap_T** root, Treap_T* parent);

#endif
