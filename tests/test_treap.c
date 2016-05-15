#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treap.h"
#define LINE_BUFFER 256

int compare_string (const void * data, const void * other_data) {
  return strcmp((char *) data, (char *) other_data);
}

void print_tree (Treap_T* node, int level) {
  int i;
  char* position;
  if (node->right_child) {
    print_tree(node->right_child, level+1);
  }
  for (i = 0; i < level; i++) {
    printf("\t");
  }
  if (node->position == LEFT) {
    position = "LEFT";
  } else if (node->position == RIGHT) {
    position = "RIGHT";
  } else {
    position = "ROOT";
  }
  printf("<- (%s %s %d)\n", position, (char *) node->data, node->priority);
  if (node->left_child) {
    print_tree(node->left_child, level+1);
  }
}

int main (int argc, const  char* argv[] ) {
  char* read_result = NULL;
  int num_lines = 0;
  int i = 0;
  int count = 0;
  Treap_T** treap = new_treap();
  Treap_T* aux = NULL;
  int* data = NULL;
  char line[LINE_BUFFER];
  read_result = fgets(line, sizeof(line), stdin);
  if (!read_result) {
    printf("Buffer insufficient!");
  }
  num_lines = atoi(line);

  for (i = 0; i < num_lines; i++) {
    read_result = fgets(line, sizeof(line), stdin);
    if (!read_result) {
      printf("Buffer insufficient!");
    }
    char op = line[0];
    char* string_to_evaluate = &(line[2]);
    string_to_evaluate[strlen(string_to_evaluate)-1] = '\0';
    switch (op) {
      case 'A' :
        /*printf("\nOP ADD=%s\n", string_to_evaluate);*/
        if (!*treap) {
          /* treap is being inited, continue */
          count = 1;
          *treap = new_t(string_to_evaluate, (void *) &count, strlen(string_to_evaluate) + 1, sizeof(int));
          printf("1\n");
          continue;
        } else {
          count = 0;
          aux = search_add_t(treap, string_to_evaluate, (void *) &count,
            strlen(string_to_evaluate) + 1, sizeof(int), compare_string);
          data = (int *) aux->data;
          *data += 1;
          printf("%d\n", *data);
        }
        break;
      case 'F' :
        /*printf("\nOP FIND=%s\n", string_to_evaluate);*/
        aux = search_t(treap, string_to_evaluate, compare_string);
        if (!aux) {
          printf("NULL\n");
        } else {
          data = (int *) aux->data;
          printf("%d\n", *data);
        }
        break;
      case 'D' :
        /*printf("\nOP DEL=%s\n", string_to_evaluate);*/
        aux = search_t(treap, string_to_evaluate, compare_string);
        if (!aux) {
          printf("NULL\n");
          continue;
        }
        data = (int *) aux->data;
        printf("%d\n", *data);
        remove_t(treap, string_to_evaluate, compare_string);
        break;
    }
    /* printf("\n====TREAP BEGIN====\n");
    print_tree(*treap, 0);
    printf("\n========\n"); */
  }
  return 0;
}
