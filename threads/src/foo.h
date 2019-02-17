#ifndef  THREADS_SRC_FOO_H_
#define  THREADS_SRC_FOO_H_

#include <string>
#include <regex>

class Foo{
  public:
    void Calc(int value, int value2);
    int Get();
  private:
    int value_;
};

#endif  //  THREADS_SRC_FOO_H_
