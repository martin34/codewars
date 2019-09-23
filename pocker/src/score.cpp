#include "score.h"

namespace pocker {
bool operator<(const Score &lhs, const Score &rhs) {
  if (lhs.GetType() < rhs.GetType()) {
    return true;
  } else if (lhs.GetType() == rhs.GetType()) {
    auto lhs_tie_breakers = lhs.GetTieBreakers();
    auto rhs_tie_breakers = rhs.GetTieBreakers();
    auto lhs_tie_breakers_it = lhs_tie_breakers.cbegin();
    auto rhs_tie_breakers_it = rhs_tie_breakers.cbegin();
    for (; lhs_tie_breakers_it != lhs_tie_breakers.cend() &&
           rhs_tie_breakers_it != rhs_tie_breakers.cend();
         ++lhs_tie_breakers_it, ++rhs_tie_breakers_it) {
      if ((*lhs_tie_breakers_it).face_value <
          (*rhs_tie_breakers_it).face_value) {
        return true;
      }
    }
  }
  return false;
}
} // namespace pocker