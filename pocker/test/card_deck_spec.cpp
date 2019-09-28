#include <algorithm>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "pocker/card_deck.h"

namespace {
using namespace testing;
using namespace pocker;

TEST(CardOperatorSpec, SmallerFaceValue) {
  Card lhs{Heart, Two};
  Card rhs{Heart, Three};
  EXPECT_THAT(lhs, Lt(rhs));
}
TEST(CardOperatorSpec, SmallerSuit) {
  Card lhs{Heart, Two};
  Card rhs{Tile, Two};
  EXPECT_THAT(lhs, Lt(rhs));
}
TEST(CardOperatorSpec, GreaterSuit) {
  Card lhs{Heart, Three};
  Card rhs{Tile, Two};
  EXPECT_THAT(lhs, Gt(rhs));
}
TEST(CardOperatorSpec, EqualSuit) {
  Card lhs{Tile, Three};
  Card rhs{Tile, Three};
  EXPECT_THAT(lhs, Eq(rhs));
}
TEST(CardDeckSpeck, NumberOfCardsWhenConstructed) {
  CardDeck deck{};

  EXPECT_THAT(deck.CardsLeft(), Eq(52));
}
TEST(CardDeckSpeck, CardsInDeckAreUniqueWhenConstructed) {
  CardDeck deck{};
  auto cards = deck.GetAllCards();
  std::sort(cards.begin(), cards.end());
  auto new_end_it = std::unique(cards.begin(), cards.end());
  bool cards_are_unique = new_end_it == cards.end();
  EXPECT_THAT(cards_are_unique, Eq(true));
  EXPECT_THAT(deck.CardsLeft(), Eq(52));
}
TEST(CardDeckSpeck, DrawOneCard) {
  CardDeck deck{};
  Card expected_card{Heart, Two};
  auto card = deck.Draw(expected_card);
  EXPECT_THAT(deck.CardsLeft(), Eq(51));
  EXPECT_THAT(expected_card, Eq(card));
}
TEST(CardDeckSpeck, DrawTwoCards) {
  CardDeck deck{};
  Card expected_card{Heart, Two};
  Card expected_card2{Heart, Three};
  auto card = deck.Draw(expected_card);
  auto card2 = deck.Draw(expected_card2);
  EXPECT_THAT(deck.CardsLeft(), Eq(50));
  EXPECT_THAT(expected_card, Eq(card));
  EXPECT_THAT(expected_card2, Eq(card2));
}
TEST(CardDeckSpeck, DrawSameCardTwice) {
  CardDeck deck{};
  Card expected_card{Heart, Three};
  Card expected_card2{Heart, Three};
  std::ignore = deck.Draw(expected_card);
  EXPECT_THROW(deck.Draw(expected_card2), std::logic_error);
}

} // namespace
