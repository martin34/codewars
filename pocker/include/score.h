#pragma once

#include "card.h"
#include <optional>

namespace pocker {
class Score {
public:
  enum ScoreType {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
  };
  Score(Score::ScoreType type) : type_{type} {}
  Score(Score::ScoreType type, Card first_tie_breaker)
      : type_{type}, first_tie_breaker_{first_tie_breaker} {}
  ScoreType GetType() const { return type_; };
  std::optional<Card> GetFirstTieBreaker() const { return first_tie_breaker_; };

private:
  ScoreType type_;
  std::optional<Card> first_tie_breaker_{};
};
inline bool operator<(const Score &lhs, const Score &rhs) {
  return lhs.GetType() < rhs.GetType();
}
inline bool operator>(const Score &lhs, const Score &rhs) { return rhs < lhs; }
inline bool operator<=(const Score &lhs, const Score &rhs) {
  return !(lhs > rhs);
}
inline bool operator>=(const Score &lhs, const Score &rhs) {
  return !(lhs < rhs);
}
inline bool operator==(const Score &lhs, const Score &rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}
} // namespace pocker