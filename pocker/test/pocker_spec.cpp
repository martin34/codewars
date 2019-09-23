#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "card_deck.h"
#include "hand.h"

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
Hand DrawLowHandWithTwoPairs() {
  return Hand{
      {Tile, Three}, {Clover, Three}, {Pike, Five}, {Heart, Ten}, {Tile, Five}};
}
Hand DrawHighHandWithTwoPairs() {
  return Hand{
      {Tile, Ace}, {Clover, Ace}, {Pike, King}, {Heart, Ten}, {Tile, Ten}};
}
Hand DrawLowHandWithThreeOfAKind() {
  return Hand{{Tile, Three},
              {Clover, Three},
              {Pike, Three},
              {Heart, Ten},
              {Tile, Eight}};
}
Hand DrawHighHandWithThreeOfAKind() {
  return Hand{
      {Tile, Ace}, {Clover, Ace}, {Pike, Ace}, {Heart, Ten}, {Tile, Eight}};
}
Hand DrawLowHandWithFourOfAKind() {
  return Hand{
      {Tile, Two}, {Clover, Two}, {Pike, Two}, {Heart, Two}, {Tile, Eight}};
}
Hand DrawHighHandWithFourOfAKind() {
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
  auto two = DrawLowHandWithThreeOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenThreeOfAKindVsFourOfAKind) {
  auto one = DrawLowHandWithThreeOfAKind();
  auto two = DrawLowHandWithFourOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenStraightVsFourOfAKind) {
  auto one = DrawHandWithStraight();
  auto two = DrawLowHandWithFourOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenThreeOfAKindVsStraight) {
  auto one = DrawLowHandWithThreeOfAKind();
  auto two = DrawHandWithStraight();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenTwoHandsWithThreeOfAKind) {
  auto one = DrawLowHandWithThreeOfAKind();
  auto two = DrawHighHandWithThreeOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenTwoHandsWithFourOfAKind) {
  auto one = DrawLowHandWithFourOfAKind();
  auto two = DrawHighHandWithFourOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenTwoPairsVsThreeOfAKind) {
  auto one = DrawLowHandWithTwoPairs();
  auto two = DrawLowHandWithThreeOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenTwoPairsVsThreeOfAKindHigh) {
  auto one = DrawLowHandWithTwoPairs();
  auto two = DrawHighHandWithThreeOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandsWithTwoPairs) {
  auto one = DrawLowHandWithTwoPairs();
  auto two = DrawHighHandWithTwoPairs();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandsWithTwoPairsSameHighPair) {
  auto one =
      Hand{{Heart, Ace}, {Pike, Ace}, {Heart, King}, {Heart, Two}, {Tile, Two}};
  auto two =
      Hand{{Tile, Ace}, {Clover, Ace}, {Pike, King}, {Heart, Ten}, {Tile, Ten}};
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandWithOnePairVsTwoPairs) {
  auto one = DrawHandWithHighPair();
  auto two = DrawLowHandWithTwoPairs();
  EXPECT_THAT(one, Lt(two));
}
} // namespace