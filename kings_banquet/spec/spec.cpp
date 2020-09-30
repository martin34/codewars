#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <numeric>

#include "fibonacci.h"
#include "graph.h"
#include "kings_table.h"

namespace {

using namespace ::testing;
TEST(KingsTable, ThrowWhenQueryNotArrangedArrangeSeating) {
  KingsTable table{34};
  EXPECT_THROW(table.NthKnightLeftToTheKing(3), std::runtime_error);
}
TEST(KingsTable, NthKnightLeftToTheKing_WhenNotEnoughSeats) {
  KingsTable table{7};
  table.ArrangeSeating();
  EXPECT_THROW(table.NthKnightLeftToTheKing(8), std::runtime_error);
}
TEST(KingsTable, Return3thsKnightOnTableWith7Seats) {
  KingsTable table{7};
  table.ArrangeSeating();
  EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(7));
}
TEST(KingsTable, Return4thsKnightOnTableWith7Seats) {
  KingsTable table{7};
  table.ArrangeSeating();
  EXPECT_THAT(table.NthKnightLeftToTheKing(4), Eq(6));
}
TEST(KingsTable, Return3thsKnightOnTableWith34Seats) {
  KingsTable table{34};
  table.ArrangeSeating();
  EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(30));
}
// TEST(KingsTable, Return3thsKnightOnTableWith34Seatsxxx) {
//   KingsTable table{99'194'853'094'755'497};
//   std::cerr << "Result is: " <<
//   table.NthKnightLeftToTheKing(10'000'000'000'000'000); FAIL();
// }

TEST(Fibonacci, CalculateUpToAtLeastN) {
  std::vector<std::uint64_t> const expected{1, 1, 2, 3, 5, 8, 13};
  auto const actual = CalculateUpToAtLeastN(9);
  EXPECT_THAT(actual, Eq(expected));
}

class IsAFibonacciNumber_WhenFalse : public TestWithParam<std::uint64_t> {};
TEST_P(IsAFibonacciNumber_WhenFalse, _) {
  EXPECT_FALSE(IsAFibonacciNumber(GetParam()));
}
class IsAFibonacciNumber_WhenTrue : public TestWithParam<std::uint64_t> {};
TEST(IsAFibonacciNumber_WhenTrue, _) { EXPECT_TRUE(IsAFibonacciNumber(1)); }
INSTANTIATE_TEST_CASE_P(Typical, IsAFibonacciNumber_WhenFalse,
                        Values(4, 6, 7, 9, 10, 11, 12));
INSTANTIATE_TEST_CASE_P(Typical, IsAFibonacciNumber_WhenTrue,
                        Values(1, 2, 3, 5, 8, 13));
} // namespace