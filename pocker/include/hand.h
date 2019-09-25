#pragma once

#include <ostream>
#include <vector>

#include "card.h"
#include "score.h"

namespace pocker {
class Hand {
public:
  using FaceValueType = std::underlying_type<FaceValue>::type;
  using SuitType = std::underlying_type<Suit>::type;
  using FaceValueTypeVector = std::vector<FaceValueType>;
  Hand(Card c0, Card c1, Card c2, Card c3, Card c4);

  Score GetMostValuableScore() const;

private:
  Card GetACardFromPair() const;
  std::optional<Score> GetPair() const;
  std::optional<Score> GetTwoPairs() const;
  std::optional<Score> GetThreeOfAKind() const;
  std::optional<Score> GetStraight() const;
  std::optional<Score> GetFlush() const;
  std::optional<Score> GetFourOfAKind() const;
  std::optional<Score> GetFullHouse() const;
  std::vector<std::vector<Card>::const_iterator> GetSecondCardOfPairs() const;
  std::vector<Card>::const_iterator GetCardPartOfPair(
      FaceValueTypeVector::const_iterator second_card_of_pair_position) const;
  std::vector<Card> GetCardsNotPartOfPair(
      std::vector<std::vector<Card>::const_iterator> second_cards_of_pair)
      const;

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
inline bool operator!=(const Hand &lhs, const Hand &rhs) {
  return !(lhs == rhs);
}
} // namespace pocker