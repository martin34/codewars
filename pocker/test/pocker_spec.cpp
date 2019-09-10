#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "pocker.h"

namespace {

using namespace testing;
using namespace pocker;

TEST(PlayerScoreSpec, WhenSameHand) {
  Hand one{
      {Pike, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  Hand two{
      {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  EXPECT_THAT(one, Eq(two));
}
TEST(PlayerScoreSpec, WhenPairs) {
  Hand one{
      {Pike, Two}, {Tile, Two}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  Hand two{
      {Heart, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}};
  EXPECT_THAT(one, Gt(two));
}

class PlayerScoreSpecParameterized
    : public TestWithParam<std::pair<Hand, Hand>> {};

TEST_P(PlayerScoreSpecParameterized, WhenHandOneLoses) {
  EXPECT_THAT(GetParam().first, Lt(GetParam().second));
}

INSTANTIATE_TEST_CASE_P(_, PlayerScoreSpecParameterized,
                        Values(
                            // clang-format off
      // WhenPairsReversed
      std::pair<Hand, Hand> {
      {{Pike, Two}, {Tile, Six}, {Clover, Three}, {Pike, Ace}, {Heart, Four}},
      {{Heart, Two}, {Tile, Two}, {Heart, Three},{Pike, Ace}, {Heart, Four}}},
      // WhenPairsAndThreeOfAKind
      std::pair<Hand, Hand> {
      {{Pike, Two}, {Tile, Two}, {Clover, Three}, {Pike, Ace}, {Heart, Four}},
      {{Heart, Two}, {Tile, Six}, {Clover, Six}, {Pike, Six}, {Heart, Four}}},
      // WhenThreeOfAKindAndFourOfAKind
      std::pair<Hand, Hand> {
      {{Heart, Three}, {Tile, Six}, {Clover, Six}, {Pike, Six}, {Heart, Four}},
      {{Pike, Two}, {Tile, Two}, {Clover, Three}, {Heart, Two}, {Clover, Two}}}
                            // clang-format on
                            ));

} // namespace