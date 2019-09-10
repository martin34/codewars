#include "pocker.h"

namespace pocker {
bool operator<(const Hand &lhs, const Hand &rhs) {
  return lhs.GetMostValuableScore() < rhs.GetMostValuableScore();
}
} // namespace pocker