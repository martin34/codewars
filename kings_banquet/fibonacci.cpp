#include "fibonacci.h"

#include <algorithm>

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
