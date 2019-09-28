#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "threads/simple_threading.h"

using namespace ::testing;

TEST(SimpleThreading, WhenEqualValues) {
  // (2 + 2) * (2 + 2)
  Foo a;
  a.Calc(2, 2);
  auto res = a.Get();
  EXPECT_THAT(res, Eq(16));
}

TEST(SimpleThreading, WhenDifferentValues) {
  // (2 + 2) * (3 + 3)
  Foo a;
  a.Calc(2, 3);
  auto res = a.Get();
  EXPECT_THAT(res, Eq(24));
}

// Next step: Share resource e. g. file between files. Two threads can not
// access this resource simultaneously --> lock Make sure to trigger confict, by
// doing a long access operation
//
// It is possilbe to use swap or atomic operations, when multiple threads acess
// the same fields.
