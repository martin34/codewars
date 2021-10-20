#include <cstdlib>
#include <tuple>

extern "C" void __cxa_throw(void *thrown_exception, void *pvtinfo,
                            void (*dest)(void *)) {
  printf(" ################ DETECT A THROWN !!!!! #############\n");
  std::abort();
  std::ignore = thrown_exception;
  std::ignore = dest;
  std::ignore = pvtinfo;
}
