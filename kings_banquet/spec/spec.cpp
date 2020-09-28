#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "graph.h"
#include <numeric>

namespace {

using namespace ::testing;

std::vector<std::uint64_t> CalculateUpToAtLeastN(std::uint64_t const n) {
  std::vector<std::uint64_t> result{1};
  std::uint64_t first{1};
  for (std::uint64_t i = 0; result.back() < n; ++i) {
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
bool IsAFibonacciNumber(std::uint64_t const n) {
  auto const fibonacci_numbers = CalculateUpToAtLeastN(n);
  return std::find(fibonacci_numbers.crbegin(), fibonacci_numbers.crend(), n) !=
         fibonacci_numbers.crend();
}

class KingsTable {
public:
  KingsTable(std::uint64_t const number_of_seats) : knights_(number_of_seats) {
    std::iota(knights_.begin(), knights_.end(), 1);
  }
  std::uint64_t NthKnightLeftToTheKing(std::uint64_t const n) {
    if (n > knights_.size()) {
      throw std::runtime_error{"Not enough seats"};
    }
    auto neighbors = FindPossibleNeighbors();

    auto graph = BuildGraphFromNeighbors(neighbors);
    // for (auto const &n : neighbors) {
    //   std::cerr << "Possible neighbors of: " << n.first << " are:";
    //   for (auto const i : n.second) {
    //     std::cerr << " " << i;
    //   }
    //   std::cerr << '\n';
    // }
    auto leafs = graph.Leafs();
    std::sort(leafs.begin(), leafs.end(),
              [](Vertex const &lhs, Vertex const &rhs) {
                return lhs.GetName() < rhs.GetName();
              });
    if (leafs.size() != 2) {
      std::cerr << "Leafs:";
      for (auto const &l : leafs) {
        std::cerr << " " << l.GetName();
      }
      std::cerr << '\n';
      throw std::runtime_error("To many knights need to be beside the king");
    }
    auto seating_order =
        graph.GetPathFromTo(leafs.at(0).GetName(), leafs.at(1).GetName());
    return seating_order[n - 1];
  }

private:
  Graph BuildGraphFromNeighbors(
      std::map<std::uint64_t, std::vector<std::uint64_t>> &neighbors) {
    for (std::uint64_t i = 1; i <= static_cast<std::uint64_t>(knights_.size());
         ++i) {
      for (auto &e : neighbors[i]) {
        if (e > i) {
          neighbors[e].push_back(i);
        }
      }
    }
    Graph graph{};
    for (auto const &vertex : neighbors) {
      graph.AddVertex(Vertex{vertex.first, vertex.second});
    }
    return graph;
  }
  std::map<std::uint64_t, std::vector<std::uint64_t>> FindPossibleNeighbors() {
    // Create pairs/s
    if (knights_.size() < 2) {
      return {};
    }
    std::map<std::uint64_t, std::vector<std::uint64_t>> neighbors{};
    auto first = knights_.cbegin();
    auto const end = knights_.cend();
    for (; first != std::prev(end); ++first) {
      std::vector<std::uint64_t> neighbors_of_first{};
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
  std::vector<std::uint64_t> knights_;
};
TEST(KingsTable, NthKnightLeftToTheKing_WhenNotEnoughSeats) {
  KingsTable table{7};
  EXPECT_THROW(table.NthKnightLeftToTheKing(8), std::runtime_error);
}
TEST(KingsTable, Return3thsKnightOnTableWith7Seats) {
  KingsTable table{7};
  EXPECT_THAT(table.NthKnightLeftToTheKing(3), Eq(7));
}
TEST(KingsTable, Return4thsKnightOnTableWith7Seats) {
  KingsTable table{7};
  EXPECT_THAT(table.NthKnightLeftToTheKing(4), Eq(6));
}
TEST(KingsTable, Return3thsKnightOnTableWith34Seats) {
  KingsTable table{34};
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