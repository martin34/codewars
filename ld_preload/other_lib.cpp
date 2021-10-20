#include "ld_preload/other_lib.h"
#include <stdexcept>

void MyThrow() { throw std::runtime_error("FooBar"); }
