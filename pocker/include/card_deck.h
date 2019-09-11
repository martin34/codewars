#pragma once

#include <vector>

#include "pocker.h"

namespace pocker {

class CardDeck {
public:
  CardDeck();

  Card Draw(Card card);

  std::int32_t CardsLeft() { return cards.size(); }
  std::vector<Card> GetAllCards() { return cards; }

private:
  std::vector<Card> cards;
};

bool operator<(const Card &lhs, const Card &rhs);
inline bool operator>(const Card &lhs, const Card &rhs) { return rhs < lhs; }
inline bool operator<=(const Card &lhs, const Card &rhs) {
  return !(lhs > rhs);
}
inline bool operator>=(const Card &lhs, const Card &rhs) {
  return !(lhs < rhs);
}
inline bool operator==(const Card &lhs, const Card &rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}
} // namespace pocker
