#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "card_deck.h"
#include "pocker.h"

namespace {

using namespace testing;
using namespace pocker;
Hand DrawHighCardHand() {
  return Hand{{Heart, Ace},
              {Tile, Queen},
              {Clover, Ten},
              {Pike, Eight},
              {Heart, {Six}}};
}
Hand DrawHandWithPair() {
  return Hand{
      {Tile, Ace}, {Clover, Ace}, {Pike, Queen}, {Heart, Ten}, {Tile, Eight}};
}
Hand DrawHandWithThreeOfAKind() {
  return Hand{
      {Tile, Ace}, {Clover, Ace}, {Pike, Ace}, {Heart, Ten}, {Tile, Eight}};
}
Hand DrawHandWithFourOfAKind() {
  return Hand{
      {Tile, Ace}, {Clover, Ace}, {Pike, Ace}, {Heart, Ace}, {Tile, Eight}};
}
TEST(PlayerScoreSpec, WhenSameHand) {
  Hand one{
      {Pike, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  Hand two{
      {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  EXPECT_THAT(one, Eq(two));
}
TEST(HandComparison, WhenHighCardVsPair) {
  auto one = DrawHandWithPair();
  auto two = DrawHighCardHand();
  EXPECT_THAT(one, Gt(two));
}
TEST(HandComparison, WhenPairVsThreeOfAKind) {
  auto one = DrawHandWithPair();
  auto two = DrawHandWithThreeOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenThreeOfAKindVsFourOfAKind) {
  auto one = DrawHandWithThreeOfAKind();
  auto two = DrawHandWithFourOfAKind();
  EXPECT_THAT(one, Lt(two));
}
} // namespace