#pragma once

#include <vector>

namespace pocker {

enum FaceValue {
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace
};

enum Suit { Heart, Tile, Clover, Pike };

struct Card {
  Card(Suit suit, FaceValue face_value) : suit(suit), face_value(face_value) {}
  Suit suit;
  FaceValue face_value;
};

enum Score {
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

class Hand {
public:
  Hand(Card c0, Card c1, Card c2, Card c3, Card c4)
      : hand{c0, c1, c2, c3, c4} {}

  Score GetMostValuableScore() const {
    auto highest_score = HighCard;
    for (auto const &card : hand) {
      int count{};
      for (auto const &others : hand) {
        if (card.face_value == others.face_value) {
          ++count;
        }
      }
      if (count == 2) {
        highest_score = OnePair;
      }
      if (count == 3) {
        highest_score = ThreeOfAKind;
      }
      if (count == 4) {
        highest_score = FourOfAKind;
      }
    }
    return highest_score;
  }

private:
  std::vector<Card> hand;
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