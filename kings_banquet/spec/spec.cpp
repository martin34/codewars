#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <numeric>

#include "kings_banquet/fibonacci.h"
#include "kings_banquet/graph.h"
#include "kings_banquet/kings_table.h"

namespace {

using namespace ::testing;
TEST(KingsTable, ThrowWhenQueryNotArrangedArrangeSeating) {
  KingsTable table{34};
  EXPECT_THROW(table.NthKnightLeftToTheKing(3), std::runtime_error);
}
TEST(KingsTable, ThrowWhenGetSeatingArrangementQueryNotArrangedArrangeSeating) {
  KingsTable table{34};
  EXPECT_THROW(table.GetSeatingArrangement(), std::runtime_error);
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
TEST(KingsTable, Return4thsKnightOnTableWith14Seats) {
  KingsTable table{14};
  EXPECT_THROW(table.ArrangeSeating(), std::runtime_error);
}
TEST(KingsTable, ReturnSeatingArrangement) {
  KingsTable table{7};
  table.ArrangeSeating();
  EXPECT_THAT(table.GetSeatingArrangement(),
              Eq(std::vector<std::uint64_t>{4, 1, 7, 6, 2, 3, 5}));
}
TEST(KingsTable, Return3thsKnightOnTableWith34Seats) {
  KingsTable table{34};
  table.ArrangeSeating();
  EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(30));
}
TEST(KingsTable, ArrangeSeatingForVariousN) {
  for (unsigned int n{0}; n < 87; ++n) {
    try {
      KingsTable table{n};
      table.ArrangeSeating();
      std::cout << "Found result for: " << n << std::endl;
    } catch (std::runtime_error &) {
      // std::cout << "No result for " << n << std::endl;
    }
  }
  // table.Debug();
}
TEST(KingsTable, Return3thsKnightOnTableWith88Seats) {
  KingsTable table{88};
  table.ArrangeSeating();
  // table.Debug();
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
TEST_P(IsAFibonacciNumber_WhenTrue, _) { EXPECT_TRUE(IsAFibonacciNumber(1)); }
INSTANTIATE_TEST_SUITE_P(Typical, IsAFibonacciNumber_WhenFalse,
                         Values(4, 6, 7, 9, 10, 11, 12));
INSTANTIATE_TEST_SUITE_P(Typical, IsAFibonacciNumber_WhenTrue,
                         Values(1, 2, 3, 5, 8, 13));
} // namespace
