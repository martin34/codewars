#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>

namespace {
using namespace ::testing;

TEST(FindPatternSpec, WhenNoMatch) {
  std::vector<std::int32_t> input{1, 2, 3, 4, 5};
  std::vector<std::int32_t> pattern{7, 8, 9};
  auto match_start = std::search(input.cbegin(), input.cend(), pattern.cbegin(),
                                 pattern.cend());
  auto match_start_3 = std::search(
      input.cbegin(), input.cend(), pattern.cbegin(), pattern.cend(),
      [](std::int32_t const &lhs, std::int32_t const &rhs) {
        return lhs == rhs;
      });
  EXPECT_THAT(match_start, Eq(input.cend()));
  EXPECT_THAT(match_start_3, Eq(input.cend()));
}
TEST(FindPatternSpec, WhenPatternLongerThanInput) {
  std::vector<std::int32_t> input{1, 2};
  std::vector<std::int32_t> pattern{7, 8, 9};
  auto match_start = std::search(input.cbegin(), input.cend(), pattern.cbegin(),
                                 pattern.cend());
  auto match_start_3 = std::search(
      input.cbegin(), input.cend(), pattern.cbegin(), pattern.cend(),
      [](std::int32_t const &lhs, std::int32_t const &rhs) {
        return lhs == rhs;
      });
  EXPECT_THAT(match_start, Eq(input.cend()));
  EXPECT_THAT(match_start_3, Eq(input.cend()));
}
TEST(FindPatternSpec, WhenMatch) {
  std::vector<std::int32_t> input{1, 2, 3, 4, 5};
  std::vector<std::int32_t> pattern{2, 3};
  auto match_start = std::search(input.cbegin(), input.cend(), pattern.cbegin(),
                                 pattern.cend());
  auto match_start_3 = std::search(
      input.cbegin(), input.cend(), pattern.cbegin(), pattern.cend(),
      [](std::int32_t const &lhs, std::int32_t const &rhs) {
        return lhs == rhs;
      });
  EXPECT_THAT(match_start, Eq(std::next(input.cbegin())));
  EXPECT_THAT(match_start_3, Eq(std::next(input.cbegin())));
}
TEST(FindPatternSpec, WhenMisMatchAtEndOfPattern) {
  std::vector<std::int32_t> input{1, 2, 3, 4, 5};
  std::vector<std::int32_t> pattern{2, 6};
  auto match_start = std::search(input.cbegin(), input.cend(), pattern.cbegin(),
                                 pattern.cend());
  auto match_start_3 = std::search(
      input.cbegin(), input.cend(), pattern.cbegin(), pattern.cend(),
      [](std::int32_t const &lhs, std::int32_t const &rhs) {
        return lhs == rhs;
      });
  EXPECT_THAT(match_start, Eq(input.cend()));
  EXPECT_THAT(match_start_3, Eq(input.cend()));
}
TEST(FindPatternSpec, WhenMatchBecauseOfDontCare) {
  std::vector<std::int32_t> input{1, 2, 3, 4, 5};
  std::vector<std::int32_t> pattern{2,
                                    std::numeric_limits<std::int32_t>::max()};
  auto match_start_3 = std::search(
      input.cbegin(), input.cend(), pattern.cbegin(), pattern.cend(),
      [](std::int32_t const &lhs, std::int32_t const &rhs) {
        return (lhs == rhs) ||
               (rhs == std::numeric_limits<std::int32_t>::max());
      });
  EXPECT_THAT(match_start_3, Eq(std::next(input.cbegin())));
}
} // namespace