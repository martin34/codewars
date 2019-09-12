#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "card_deck.h"
#include "pocker.h"

namespace {

using namespace testing;
using namespace pocker;
Hand DrawHandWithHighHightCard() {
  return Hand{
      {Heart, Ace}, {Tile, Queen}, {Clover, Ten}, {Pike, Eight}, {Heart, Six}};
}
Hand DrawHandWithLowHightCard() {
  return Hand{
      {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, King}, {Heart, Four}};
}
Hand DrawHandWithLowPair() {
  return Hand{{Tile, Seven},
              {Clover, Seven},
              {Pike, Queen},
              {Heart, Ten},
              {Tile, Eight}};
}
Hand DrawHandWithHighPair() {
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
Hand DrawHandWithStraight() {
  return Hand{
      {Tile, Ace}, {Clover, Queen}, {Pike, King}, {Heart, Ten}, {Tile, Jack}};
}
TEST(PlayerScoreSpec, WhenSameHand) {
  Hand one{
      {Pike, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  Hand two{
      {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  EXPECT_THAT(one, Eq(two));
}

TEST(PlayerScoreSpec, WhenHandsWithHighCard) {
  auto one = DrawHandWithHighHightCard();
  auto two = DrawHandWithLowHightCard();
  EXPECT_THAT(one, Gt(two));
}
TEST(HandComparison, WhenHighCardVsPair) {
  auto one = DrawHandWithLowPair();
  auto two = DrawHandWithHighHightCard();
  EXPECT_THAT(one, Gt(two));
}
TEST(HandComparison, WhenHandsWithPair) {
  auto one = DrawHandWithLowPair();
  auto two = DrawHandWithHighPair();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenPairVsThreeOfAKind) {
  auto one = DrawHandWithLowPair();
  auto two = DrawHandWithThreeOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenThreeOfAKindVsFourOfAKind) {
  auto one = DrawHandWithThreeOfAKind();
  auto two = DrawHandWithFourOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenStraightVsFourOfAKind) {
  auto one = DrawHandWithStraight();
  auto two = DrawHandWithFourOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenThreeOfAKindVsStraight) {
  auto one = DrawHandWithThreeOfAKind();
  auto two = DrawHandWithStraight();
  EXPECT_THAT(one, Lt(two));
}
} // namespace