#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>
#include <tuple>
#include <variant>

namespace {
using namespace testing;

TEST(Varinat, GetFirst) {
  int value{3};
  std::variant<int, float> v{value};
  EXPECT_THAT(std::get<int>(v), Eq(value));
}
TEST(Varinat, GetSecond) {
  float value{3.0f};
  std::variant<int, float> v{value};
  EXPECT_THAT(std::get<float>(v), FloatEq(value));
}
TEST(Varinat, GetNotSet) {
  float value{3.0f};
  std::variant<int, float> v{value};
  EXPECT_THROW(std::get<int>(v), std::bad_variant_access);
}
TEST(Varinat, CheckIfSet) {
  float value{3.0f};
  std::variant<int, float> v{value};
  EXPECT_THAT(std::holds_alternative<float>(v), Eq(true));
  EXPECT_THAT(std::holds_alternative<int>(v), Eq(false));
  EXPECT_THAT(v.index(), Eq(1));
}
TEST(Varinat, ExchangeValue) {
  float value{3.0f};
  std::variant<int, float> v{value};
  v.emplace<int>(4);
  EXPECT_THAT(std::holds_alternative<float>(v), Eq(false));
  EXPECT_THAT(std::holds_alternative<int>(v), Eq(true));
  EXPECT_THAT(v.index(), Eq(0));
}
std::string int_to_string(int value) { return std::to_string(value); }
TEST(Variant, Visit) {
  float value{3.0f};
  std::variant<int, float> v{value};
  auto res =
      std::visit(int_to_string, v); // Why does this compile with -Wconversion
  EXPECT_THAT(res, Eq(std::to_string(static_cast<int>(value))));
}
} // namespace
