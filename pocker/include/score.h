#pragma once

#include "card.h"
#include <algorithm>
#include <optional>
#include <vector>

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
      : type_{type}, tie_breakers_{first_tie_breaker} {}
  Score(Score::ScoreType type, Card first_tie_breaker, Card second_tie_breaker)
      : type_{type}, tie_breakers_{first_tie_breaker, second_tie_breaker} {}

  template <class InputIt>
  Score(Score::ScoreType type, InputIt begin, InputIt end) : type_{type} {
    std::copy(begin, end, std::back_inserter(tie_breakers_));
  }
  ScoreType GetType() const { return type_; }

  void AddNextTieBreaker(Card card) { tie_breakers_.push_back(card); }

  std::vector<Card> GetTieBreakers() const { return tie_breakers_; }

private:
  ScoreType type_;
  std::vector<Card> tie_breakers_{};
};

bool operator<(const Score &lhs, const Score &rhs);
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