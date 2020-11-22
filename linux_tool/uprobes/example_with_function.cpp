#include <stdio.h>

char add_one(char n) { return n + 1; }

void print(char n) { printf("Number: %c\n", add_one(n)); }

int main(int argc, char *argv[]) {
  if (argc == 2) {
    print(argv[1][0]);
  }
  return 0;
}
