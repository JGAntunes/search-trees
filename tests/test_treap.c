#include <stdio.h>
#include <string.h>
#include "treap.h"
#define LINE_BUFFER 256

int main (int argc, const  char* argv[] ) {
  if (argc < 3) {
    printf("Correct usage ./<test_treap_exe> <in_file> <out_file>\n");
    return 1;
  }
  char const* const in_file_name = argv[1];
  char const* const out_file_name = argv[2];
  FILE* in_file = fopen(in_file_name, "r"); /* should check the result */
  FILE* out_file = fopen(out_file_name, "w"); /* should check the result */
  char line[LINE_BUFFER];
  while (fgets(line, sizeof(line), in_file)) {
    /*handle lines longer that sizeof(line) */
    printf("%s", line);
  }

  fclose(in_file);
  fclose(out_file);

  return 0;
}
