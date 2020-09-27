#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <numeric>

namespace {

using namespace ::testing;

std::vector<std::int32_t> CalculateUpToAtLeastN(std::int32_t const n) {
  std::vector<std::int32_t> result{1};
  std::int32_t first{1};
  for (std::int32_t i = 0; result.back() < n; ++i) {
    if (i < 1) {
      result.push_back(first);
    } else {
      decltype(result)::const_iterator second_to_last{
          std::prev(std::prev(result.cend()))};
      result.push_back(result.back() + *second_to_last);
    }
  }
  return result;
}
bool IsAFibonacciNumber(std::int32_t const n) {
  auto const fibonacci_numbers = CalculateUpToAtLeastN(n);
  return std::find(fibonacci_numbers.crbegin(), fibonacci_numbers.crend(), n) !=
         fibonacci_numbers.crend();
}

class KingsTable {
public:
  KingsTable(std::int32_t const number_of_seats) : nights_(number_of_seats) {
    std::iota(nights_.begin(), nights_.end(), 1);
  }
  std::int32_t NthKnightLeftToTheKing(std::uint32_t const n) {
    if (n > nights_.size()) {
      throw std::runtime_error{"Not enough seats"};
    }
    auto neighbors = FindPossibleNeighbors();
    for (auto const &n : neighbors) {
      std::cerr << "Possible neighbors of: " << n.first << " are:";
      for (auto const i : n.second) {
        std::cerr << " " << i;
      }
      std::cerr << '\n';
    }
    return 7;
  }

private:
  std::map<std::int32_t, std::vector<std::int32_t>> FindPossibleNeighbors() {
    // Create pairs/s
    if (nights_.size() < 2) {
      return {};
    }
    std::map<std::int32_t, std::vector<std::int32_t>> neighbors{};
    auto first = nights_.cbegin();
    auto const end = nights_.cend();
    for (; first != std::prev(end); ++first) {
      std::vector<std::int32_t> neighbors_of_first{};
      auto second = std::next(first);
      for (; second != end; ++second) {
        // Sum
        auto const sum = *first + *second;
        // Keep if Fibonacci
        if (IsAFibonacciNumber(sum)) {
          neighbors_of_first.push_back(*second);
        }
      }
      neighbors.emplace(std::make_pair(*first, neighbors_of_first));
    }
    return neighbors;
  }

private:
  std::vector<std::int32_t> nights_;
};
TEST(KingsTable, NthKnightLeftToTheKing_WhenNotEnoughSeats) {
  KingsTable table{7};
  EXPECT_THROW(table.NthKnightLeftToTheKing(8), std::runtime_error);
}
// TEST(KingsTable, Return3thsKnightOnTableWith7Seats) {
//   KingsTable table{7};
//   EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(7));
// }
// TEST(KingsTable, Return4thsKnightOnTableWith7Seats) {
//   KingsTable table{7};
//   EXPECT_THAT(table.NthKnightLeftToTheKing(4), Eq(6));
// }
// TEST(KingsTable, Return3thsKnightOnTableWith34Seats) {
//     KingsTable table{34};
//     EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(30));
// }

TEST(Fibonacci, CalculateUpToAtLeastN) {
  std::vector<std::int32_t> const expected{1, 1, 2, 3, 5, 8, 13};
  auto const actual = CalculateUpToAtLeastN(9);
  EXPECT_THAT(actual, Eq(expected));
}

class IsAFibonacciNumber_WhenFalse : public TestWithParam<std::int32_t> {};
TEST_P(IsAFibonacciNumber_WhenFalse, _) {
  EXPECT_FALSE(IsAFibonacciNumber(GetParam()));
}
class IsAFibonacciNumber_WhenTrue : public TestWithParam<std::int32_t> {};
TEST(IsAFibonacciNumber_WhenTrue, _) { EXPECT_TRUE(IsAFibonacciNumber(1)); }
INSTANTIATE_TEST_CASE_P(Typical, IsAFibonacciNumber_WhenFalse,
                        Values(-5, -1, 4, 6, 7, 9, 10, 11, 12));
INSTANTIATE_TEST_CASE_P(Typical, IsAFibonacciNumber_WhenTrue,
                        Values(1, 2, 3, 5, 8, 13));
} // namespace