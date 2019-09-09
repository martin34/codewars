#include "gmock/gmock.h"
#include "gtest/gtest.h"

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
    for (auto const &card : hand) {
      int count{};
      for (auto const &others : hand) {
        if (card.face_value == others.face_value) {
          ++count;
        }
      }
      if (count == 2) {
        return OnePair;
      }
    }
    return HighCard;
  }

private:
  std::vector<Card> hand;
};

// Shall contain simple logic like
// lhs.MostValuableScore() -> TwoPairs/Pair/Flush/...
// lhs.GetHighestCard()
bool operator<(const Hand &lhs, const Hand &rhs) {
  return lhs.GetMostValuableScore() < rhs.GetMostValuableScore();
}
bool operator>(const Hand &lhs, const Hand &rhs) { return !(lhs < rhs); }
// bool operator==(const Hand &lhs, const Hand &rhs) {
//   return lhs < rhs;
// }
namespace {

using namespace testing;

TEST(PlayerScoreSpec, WhenPairs) {
  Hand one{
      {Heart, Two}, {Tile, Two}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  Hand two{
      {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  EXPECT_THAT(one, Gt(two));
}
TEST(PlayerScoreSpec, WhenPairsReversed) {
  Hand one{
      {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  Hand two{
      {Heart, Two}, {Tile, Two}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  EXPECT_THAT(one, Lt(two));
}
// TEST(PlayerScoreSpec, WhenSameHand) {
//   Hand one{
//       {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart,
//       Four}};
//   Hand two{
//       {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart,
//       Four}};
//   EXPECT_THAT(one, Eq(two));
// }
} // namespace