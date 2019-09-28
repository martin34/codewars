#include "csv/runner.h"
#include <iostream>

int main(int argc, char **argv) {
  auto arguments = ConvertToStrings(argc, argv);
  Runner worker{arguments, std::cout};
  worker.Do();
  return 0;
}
