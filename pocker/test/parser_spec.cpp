#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>
#include <tuple>

#include "pocker/hand.h"
#include "pocker/parser.h"

namespace {
using namespace ::testing;
using namespace pocker;

TEST(foo, bar) {
  std::string line{"AH 9S 4D 9D 8S 4H JS 3C TC 8D"};

  auto out = ParseHandsFromLine(line);

  Hand expected_hand_one{
      {Heart, Ace}, {Pike, Nine}, {Tile, Four}, {Tile, Nine}, {Pike, Eight}};
  Hand expected_hand_two{{Heart, Four},
                         {Pike, Jack},
                         {Clover, Three},
                         {Clover, Ten},
                         {Tile, Eight}};
  EXPECT_THAT(out.first, Eq(expected_hand_one));
  EXPECT_THAT(out.second, Eq(expected_hand_two));
}
TEST(foo, bar2) {
  std::string line{"TH 8H 5C QS TC 9H 4D JC KS JS"};

  auto out = ParseHandsFromLine(line);

  Hand expected_hand_one{{Heart, Ten},
                         {Heart, Eight},
                         {Clover, Five},
                         {Pike, Queen},
                         {Clover, Ten}};
  Hand expected_hand_two{
      {Heart, Nine}, {Tile, Four}, {Clover, Jack}, {Pike, King}, {Pike, Jack}};
  EXPECT_THAT(out.first, Eq(expected_hand_one));
  EXPECT_THAT(out.second, Eq(expected_hand_two));
}
} // namespace