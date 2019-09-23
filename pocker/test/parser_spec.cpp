#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>
#include <tuple>

#include "hand.h"

namespace {
using namespace ::testing;
using namespace pocker;

std::pair<Hand, Hand> ParseHandsFromLine(std::string const &line) {
  std::ignore = line;
  Hand expected_hand_one{
      {Heart, Ace}, {Pike, Nine}, {Tile, Four}, {Tile, Nine}, {Pike, Eight}};
  Hand expected_hand_two{{Heart, Four},
                         {Pike, Jack},
                         {Clover, Three},
                         {Clover, Ten},
                         {Tile, Eight}};

  return {expected_hand_one, expected_hand_two};
}

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
} // namespace