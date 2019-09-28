#ifndef THREADS_SRC_FOO_H_
#define THREADS_SRC_FOO_H_

#include "auto_join_thread.h"
#include <regex>
#include <string>

class Foo {
public:
  void Calc(int value, int value2);
  int Get();

private:
  int value_;
};

#endif //  THREADS_SRC_FOO_H_
