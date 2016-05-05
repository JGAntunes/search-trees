#include <stdio.h>
#include <string.h>
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
  if (argc < 3) {
    printf("Correct usage ./<test_treap_exe> <in_file> <out_file>\n");
    return 1;
  }
  char const* const in_file_name = argv[1];
  char const* const out_file_name = argv[2];
  /* int num_lines = 0; */
  FILE* in_file = fopen(in_file_name, "r"); /* should check the result */
  FILE* out_file = fopen(out_file_name, "w"); /* should check the result */
  char line[LINE_BUFFER];
  Treap_T** treap = new_treap();
  fgets(line, sizeof(line), in_file);
  /* num_lines = atoi(line); */
  while (fgets(line, sizeof(line), in_file)) {
    /*handle lines longer that sizeof(line) */
    char op = line[0];
    char* string_to_evaluate = &(line[2]);
    string_to_evaluate[strlen(string_to_evaluate)-1] = '\0';
    switch (op) {
      case 'A' :
        printf("\nOP ADD=%s\n", string_to_evaluate);
        if (!*treap) {
          *treap = new_t(string_to_evaluate, strlen(string_to_evaluate) + 1);
        } else {
          add_t(treap, string_to_evaluate, strlen(string_to_evaluate) + 1, compare_string);
        }
        break;
      case 'F' :
        printf("\nOP FIND=%s\n", string_to_evaluate);
        search_t(treap, string_to_evaluate, compare_string);
        break;
      case 'D' :
        printf("\nOP DEL=%s\n", string_to_evaluate);
        remove_t(treap, string_to_evaluate, compare_string);
        break;
    }
    printf("\n====TREAP BEGIN====\n");
    print_tree(*treap, 0);
    printf("\n========\n");
  }

  fclose(in_file);
  fclose(out_file);

  return 0;
}
