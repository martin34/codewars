#pragma once

#include <algorithm>
#include <ostream>
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
std::ostream &operator<<(std::ostream &os, const FaceValue &p);

enum Suit { Heart, Tile, Clover, Pike };
std::ostream &operator<<(std::ostream &os, const Suit &p);

struct Card {
  Card(Suit suit, FaceValue face_value) : suit(suit), face_value(face_value) {}
  Suit suit;
  FaceValue face_value;
};
std::ostream &operator<<(std::ostream &os, const Card &p);

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
  Hand(Card c0, Card c1, Card c2, Card c3, Card c4) : hand{c0, c1, c2, c3, c4} {
    std::sort(hand.begin(), hand.end(), [](Card const &lhs, Card const &rhs) {
      return lhs.face_value < rhs.face_value;
    });
  }

  Score GetMostValuableScore() const;

private:
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