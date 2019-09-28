#include <algorithm>
#include <stdexcept>

#include "pocker/card_deck.h"

namespace pocker {

CardDeck::CardDeck() {
  constexpr std::initializer_list<Suit> all_suits = {Heart, Tile, Clover, Pike};
  constexpr std::initializer_list<FaceValue> all_face_values = {
      Two,  Three, Four, Five,  Six,  Seven, Eight,
      Nine, Ten,   Jack, Queen, King, Ace};

  for (auto s : all_suits) {
    for (auto f : all_face_values) {
      cards.push_back({s, f});
    }
  }
}
Card CardDeck::Draw(Card card) {
  auto it = std::find(cards.begin(), cards.end(), card);
  if (it != cards.end()) {
    cards.erase(it);
  } else {
    throw std::logic_error("Card not in card deck");
  }
  return card;
}

bool operator<(const Card &lhs, const Card &rhs) {
  bool smaller = lhs.face_value < rhs.face_value;
  if (lhs.face_value == rhs.face_value) {
    smaller = lhs.suit < rhs.suit;
  }
  return smaller;
}
} // namespace pocker