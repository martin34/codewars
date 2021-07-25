#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using testing::HasSubstr;

std::string MyFunction() { return std::string{__FUNCTION__}; }

TEST(SpecialFunctions, Function) {
  const auto name = MyFunction();
  std::cerr << name << '\n';
  EXPECT_THAT(name, HasSubstr("MyFunction"));
}

std::string MyPrettyFunction() { return std::string{__PRETTY_FUNCTION__}; }

TEST(SpecialFunctions, PrettyFunction) {
  const auto name = MyPrettyFunction();
  std::cerr << name << '\n';
  EXPECT_THAT(name, HasSubstr("MyPrettyFunction"));
}

std::string MyPrettyFunctionWithArgs(int, std::string) {
  std::cerr << __PRETTY_FUNCTION__ << '\n';
  return std::string{__PRETTY_FUNCTION__};
}

TEST(SpecialFunctions, PrettyFunctionWithArgs) {
  const auto name = MyPrettyFunctionWithArgs(3, std::string{});
  std::cerr << name << '\n';
  EXPECT_THAT(name, HasSubstr("MyPrettyFunctionWithArgs"));
}
} // namespace
