#ifndef TREAP_H
#define TREAP_H

typedef struct Treap_T{
    int priority;
    void* data;
    struct Treap_T* parent;
    struct Treap_T* left_child;
    struct Treap_T* right_child;
} Treap_T;

typedef enum { false, true } bool;

Treap_T* new_t(void* data);

void add_t(Treap_T* root, Treap_T* node);

void remove_t(Treap_T* root, void* data);

void rotate_left(Treap_T* parent);

void rotate_left(Treap_T* parent);

void rotate_right(Treap_T* parent);

#endif