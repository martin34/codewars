#include "split.h"
#include <sstream>

namespace utils {
std::vector<std::string> Split(const std::string &str, char delim) {
  std::stringstream ss(str);
  std::string token;
  std::vector<std::string> output;
  while (std::getline(ss, token, delim)) {
    output.push_back(token);
  }
  return output;
}
} // namespace utils