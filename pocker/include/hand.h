#pragma once

#include <ostream>
#include <vector>

#include "card.h"
#include "score.h"

namespace pocker {
class Hand {
public:
  Hand(Card c0, Card c1, Card c2, Card c3, Card c4);

  Score GetMostValuableScore() const;

private:
  bool HasPair() const;
  Card GetACardFromPair() const;
  bool HasThreeOfAKind() const;
  bool HasFourOfAKind() const;
  bool HasStraight() const;

  std::vector<Card> hand;
  friend std::ostream &operator<<(std::ostream &os, const Hand &p);
};

// Shall contain simple logic like
// lhs.MostValuableScore() -> TwoPairs/Pair/Flush/...
// lhs.GetHighestCard()
bool operator<(const Hand &lhs, const Hand &rhs);
inline bool operator>(const Hand &lhs, const Hand &rhs) { return rhs < lhs; }
inline bool operator<=(const Hand &lhs, const Hand &rhs) {
  return !(lhs > rhs);
}
inline bool operator>=(const Hand &lhs, const Hand &rhs) {
  return !(lhs < rhs);
}
inline bool operator==(const Hand &lhs, const Hand &rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}
} // namespace pocker