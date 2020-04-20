#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "templates/log.h"
#include <cstdint>

namespace {

using namespace ::testing;
using namespace templates;

TEST(Log, WhenNotSupportedType) {
  class NotSupportedType {};
  auto result = to_string(NotSupportedType{});
  EXPECT_THAT(result, Eq(kNotSupportedOutput));
}
TEST(Log, WhenInt) {
  int some_int{22};
  auto result = to_string(some_int);
  EXPECT_THAT(result, Eq("22"));
}
TEST(Log, WhenInt32) {
  std::int32_t some_int{22};
  auto result = to_string(some_int);
  EXPECT_THAT(result, Eq("22"));
}
TEST(Log, WhenInt64) {
  std::int64_t some_int{22};
  auto result = to_string(some_int);
  EXPECT_THAT(result, Eq("22"));
}
TEST(Log, WhenDouble) {
  double some_int{22.};
  auto result = to_string(some_int);
  EXPECT_THAT(result, Eq("Double value impl"));
}
} // namespace