#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "a.h"
#include "b.h"

namespace {

using ::testing::Eq;

TEST(A, Function) {
  B b{};
  AFunction(b);
  EXPECT_THAT(b.GetCount(), Eq(1));
}
TEST(A, Class) {
  B b{};
  A a{b};
  a.Do();
  EXPECT_THAT(b.GetCount(), Eq(2));
}
} // namespace