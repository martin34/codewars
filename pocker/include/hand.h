#pragma once

#include <ostream>
#include <vector>

#include "card.h"
#include "score.h"

namespace pocker {
class Hand {
public:
  using FaceValueType = std::underlying_type<FaceValue>::type;
  using FaceValueTypeVector = std::vector<FaceValueType>;
  Hand(Card c0, Card c1, Card c2, Card c3, Card c4);

  Score GetMostValuableScore() const;

private:
  Card GetACardFromPair() const;
  std::optional<Score> GetPair() const;
  std::optional<Score> GetTwoPairs() const;
  std::optional<Score> GetThreeOfAKind() const;
  std::optional<Score> GetStraight() const;
  std::optional<Score> GetFourOfAKind() const;

  std::vector<Card> hand_;
  FaceValueTypeVector face_value_adjacent_diff_{};
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