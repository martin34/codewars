#include "log.h"

namespace templates {

template <> std::string to_string(double) {
  return std::string{"Double value impl"};
}

} // namespace templates