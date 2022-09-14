#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>
#include <string_view>

namespace {

using ::testing::Eq;
using ::testing::Ne;

TEST(StringView, BasicFunctionalityString) {
  const std::string a_string{"abc"};
  const std::string_view a_string_view{a_string};

  EXPECT_THAT(a_string_view, Eq("abc"));
  EXPECT_THAT(a_string_view, Eq(a_string));
}
TEST(StringView, BasicFunctionalityChars) {
  const char *a_string{"abc"};
  const std::string_view a_string_view{a_string, 2};
  EXPECT_THAT(a_string_view, Eq("ab"));
  EXPECT_THAT(a_string_view, Ne(a_string));
}
TEST(StringView, Manipulation) {
  std::string a_string{"abc"};
  std::string_view a_string_view{a_string};

  a_string = "def";
  EXPECT_THAT(a_string_view, Eq("def"));
}
TEST(StringView, OutOfBoundWhenUsedWithoutCare) {
  std::string a_string{"abc"};
  std::string_view a_string_view{a_string};

  a_string.clear();
  a_string.resize(0);
  EXPECT_THAT(a_string_view.size(), Eq(3));
}
} // namespace
