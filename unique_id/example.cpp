#include "example.h"

std::int32_t GenerateId() {
  static std::int32_t id;
  return id++;
}
