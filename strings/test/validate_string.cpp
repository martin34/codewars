#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>
#include <string>

namespace {

bool IsValidColor(char value) { return 'a' <= value && value <= 'm'; }

std::string CalculateErrorRate(std::string const &colors) {
  const auto invalid_count{static_cast<std::uint32_t>(
      std::count_if(colors.cbegin(), colors.cend(), IsValidColor))};
  return std::to_string(colors.length() - invalid_count) + std::string{"/"} +
         std::to_string(colors.length());
}

using namespace ::testing;

TEST(ErrorRate, ValidInput) {
  std::string valid_colors{"abcfgh"};
  std::string expected{"0/6"};

  auto actual = CalculateErrorRate(valid_colors);

  EXPECT_THAT(actual, Eq(expected));
}
TEST(ErrorRate, ValidInputLong) {
  std::string valid_colors{"abcfghghiac"};
  std::string expected{"0/11"};

  auto actual = CalculateErrorRate(valid_colors);

  EXPECT_THAT(actual, Eq(expected));
}
TEST(ErrorRate, OneError) {
  std::string valid_colors{"abcfghn"};
  std::string expected{"1/7"};

  auto actual = CalculateErrorRate(valid_colors);

  EXPECT_THAT(actual, Eq(expected));
}
TEST(ErrorRate, OneOtherError) {
  std::string valid_colors{"abxcfgh"};
  std::string expected{"1/7"};

  auto actual = CalculateErrorRate(valid_colors);

  EXPECT_THAT(actual, Eq(expected));
}
TEST(ErrorRate, TwoErrors) {
  std::string valid_colors{"abxcsgh"};
  std::string expected{"2/7"};

  auto actual = CalculateErrorRate(valid_colors);

  EXPECT_THAT(actual, Eq(expected));
}
TEST(ErrorRate, EmptyInput) {
  std::string valid_colors{""};
  std::string expected{"0/0"};

  auto actual = CalculateErrorRate(valid_colors);

  EXPECT_THAT(actual, Eq(expected));
}

struct Params {
  Params(char input_color, bool valid)
      : input_color{input_color}, valid{valid} {}
  char input_color;
  bool valid;
};
class IsColorValidSpec : public TestWithParam<Params> {};
TEST_P(IsColorValidSpec, Valid) {
  EXPECT_THAT(IsValidColor(GetParam().input_color), Eq(GetParam().valid));
}
INSTANTIATE_TEST_SUITE_P(
    IsColorValid, IsColorValidSpec,
    Values(
        // clang-format off
            Params{'a', true},
            Params{'b', true},
            Params{'c', true},
            Params{'d', true},
            Params{'e', true},
            Params{'f', true},
            Params{'g', true},
            Params{'h', true},
            Params{'i', true},
            Params{'j', true},
            Params{'k', true},
            Params{'l', true},
            Params{'m', true},
            Params{'n', false},
            Params{'o', false},
            Params{'p', false},
            Params{'9', false},
            Params{'0', false},
            Params{'\n', false})
    // clang-format on
);
} // namespace
