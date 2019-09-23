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
Hand DrawLowHandWithFullHouse() {
  return Hand{
      {Tile, Two}, {Clover, Two}, {Pike, Two}, {Heart, Ten}, {Tile, Ten}};
}
Hand DrawHighHandWithFullHouse() {
  return Hand{
      {Tile, Ace}, {Clover, Ace}, {Pike, Ace}, {Heart, King}, {Tile, King}};
}
Hand DrawLowHandWithFlush() {
  return Hand{
      {Tile, Two}, {Tile, Seven}, {Tile, Six}, {Tile, Three}, {Tile, Five}};
}
Hand DrawHighHandWithFlush() {
  return Hand{
      {Tile, Ace}, {Tile, King}, {Tile, Jack}, {Tile, Queen}, {Tile, Nine}};
}
Hand DrawLowHandWithStraightFlush() {
  return Hand{
      {Tile, Two}, {Tile, Three}, {Tile, Four}, {Tile, Six}, {Tile, Five}};
}
Hand DrawHandWithRoyalFlush() {
  return Hand{
      {Heart, Ace}, {Heart, King}, {Heart, Queen}, {Heart, Jack}, {Heart, Ten}};
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
TEST(PlayerScoreSpec, WhenHandsWithHighCardAlmostSame) {
  Hand one{{Pike, Two}, {Tile, Six}, {Clover, Ten}, {Pike, Ace}, {Heart, King}};
  Hand two{
      {Heart, Three}, {Tile, Six}, {Clover, Ten}, {Pike, Ace}, {Heart, King}};
  EXPECT_THAT(one, Lt(two));
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
TEST(HandComparison, WhenHandsWithTwoEqualPairsHighCardWins) {
  auto one = Hand{
      {Heart, Ace}, {Pike, Ace}, {Heart, Four}, {Clover, Ten}, {Pike, Ten}};
  auto two =
      Hand{{Tile, Ace}, {Clover, Ace}, {Pike, King}, {Heart, Ten}, {Tile, Ten}};
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandWithOnePairVsTwoPairs) {
  auto one = DrawHandWithHighPair();
  auto two = DrawLowHandWithTwoPairs();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandWithThreeOfAKindVsFullHouse) {
  auto one = DrawHighHandWithThreeOfAKind();
  auto two = DrawLowHandWithFullHouse();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandWithFourOfAKindVsFullHouse) {
  auto one = DrawHighHandWithFullHouse();
  auto two = DrawLowHandWithFourOfAKind();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandWithTwoFullHouse) {
  auto one = DrawLowHandWithFullHouse();
  auto two = DrawHighHandWithFullHouse();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandWithFlushVsStraight) {
  auto one = DrawHandWithStraight();
  auto two = DrawLowHandWithFlush();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenHandWithFlushVsFullHouse) {
  auto one = DrawHighHandWithFlush();
  auto two = DrawLowHandWithFullHouse();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenTwoHandsWithFlush) {
  auto one = DrawLowHandWithFlush();
  auto two = DrawHighHandWithFlush();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenFourOfAKindVsStraightFlush) {
  auto one = DrawHighHandWithFourOfAKind();
  auto two = DrawLowHandWithStraightFlush();
  EXPECT_THAT(one, Lt(two));
}
TEST(HandComparison, WhenStraightFlushVsRoyalFlush) {
  auto one = DrawLowHandWithStraightFlush();
  auto two = DrawHandWithRoyalFlush();
  EXPECT_THAT(one, Lt(two));
}
} // namespace