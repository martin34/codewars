#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "utils/string/split.h"

namespace {
using ::testing::Eq;
TEST(SplitStringSpec, WhenTypical) {
  std::string input{"a b c d e f"};
  auto actual = utils::Split(input);
  std::vector<std::string> expect{std::string{"a"}, std::string{"b"},
                                  std::string{"c"}, std::string{"d"},
                                  std::string{"e"}, std::string{"f"}};
  EXPECT_THAT(actual, Eq(expect));
}
} // namespace