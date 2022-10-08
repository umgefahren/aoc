#include <stdio.h>
#include <stdlib.h>

struct Arrow {
  int start_x;
  int start_y;
  int end_x;
  int end_y;
};

struct Arrow read_from_file(FILE* file, int* error) {
  struct Arrow ret;

  return ret;
}

int main() {
  FILE* file = fopen("input.txt", "r");
  return 0;
}
