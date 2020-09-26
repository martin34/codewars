#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace ::testing;

class KingsTable {
public:
  KingsTable(std::int32_t const number_of_seats) {
    std::ignore = number_of_seats;
  }
  std::int32_t NthKnightLeftToTheKing(std::uint32_t const n) {
    std::ignore = n;
    return 7;
  }
};

TEST(KingsTable, Return3thsKnightOnTableWith7Seats) {
  KingsTable table{7};
  EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(7));
}
// TEST(KingsTable, Return3thsKnightOnTableWith34Seats) {
//     KingsTable table{34};
//     EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(30));
// }
std::vector<std::int32_t> CalculateUpToNthValue(std::int32_t const n) {
  std::vector<std::int32_t> result;
  std::int32_t first{1};
  for (std::int32_t i = 0; i < n; ++i) {
    if (i < 2) {
      result.push_back(first);
    } else {
      std::vector<std::int32_t>::const_iterator second_to_last{
          std::prev(std::prev(result.cend()))};
      result.push_back(result.back() + *second_to_last);
    }
  }
  return result;
}
TEST(Fibonacci, CalculateUpToNthValue) {
  std::vector<std::int32_t> const expected{1, 1, 2, 3, 5, 8, 13};
  auto const actual =
      CalculateUpToNthValue(static_cast<std::int32_t>(expected.size()));
  EXPECT_THAT(actual, Eq(expected));
}