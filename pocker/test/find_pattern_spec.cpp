#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "find_match.h"

namespace {
using namespace ::testing;
using utils::find_match;

TEST(FindPatternSpec, WhenNoMatch) {
  std::vector<std::int32_t> input{1, 2, 3, 4, 5};
  std::vector<std::int32_t> pattern{7, 8, 9};
  auto match_start = find_match(input.cbegin(), input.cend(), pattern.cbegin(),
                                pattern.cend());
  EXPECT_THAT(match_start, Eq(input.cend()));
}
TEST(FindPatternSpec, WhenPatternLongerThanInput) {
  std::vector<std::int32_t> input{1, 2};
  std::vector<std::int32_t> pattern{7, 8, 9};
  auto match_start = find_match(input.cbegin(), input.cend(), pattern.cbegin(),
                                pattern.cend());
  EXPECT_THAT(match_start, Eq(input.cend()));
}
TEST(FindPatternSpec, WhenMatch) {
  std::vector<std::int32_t> input{1, 2, 3, 4, 5};
  std::vector<std::int32_t> pattern{2, 3};
  auto match_start = find_match(input.cbegin(), input.cend(), pattern.cbegin(),
                                pattern.cend());
  EXPECT_THAT(match_start, Eq(std::next(input.cbegin())));
}
TEST(FindPatternSpec, WhenMisMatchAtEndOfPattern) {
  std::vector<std::int32_t> input{1, 2, 3, 4, 5};
  std::vector<std::int32_t> pattern{2, 6};
  auto match_start = find_match(input.cbegin(), input.cend(), pattern.cbegin(),
                                pattern.cend());
  EXPECT_THAT(match_start, Eq(input.cend()));
}
} // namespace