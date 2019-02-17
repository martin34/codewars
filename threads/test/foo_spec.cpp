#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>
#include <iostream>

#include "threads/src/foo.h"

using namespace ::testing;

TEST(foo, bar)
{
  // (2 + 2) * (2 + 2)
  Foo a;
  a.Calc(2, 2);
  auto res = a.Get();
  EXPECT_THAT(res, Eq(16));
}

TEST(foo, bar2)
{
  // (2 + 2) * (3 + 3)
  Foo a;
  a.Calc(2, 3);
  auto res = a.Get();
  EXPECT_THAT(res, Eq(24));
}
