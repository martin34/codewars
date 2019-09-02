#include "wilson_prime.h"

#include <algorithm>
#include <functional>
#include <numeric>

bool IsPrime(std::uint32_t n) {
  std::int64_t min_size = 0;
  std::int64_t max_size{static_cast<std::int64_t>(n) - 3};
  std::size_t size = std::max(min_size, max_size);
  std::vector<std::uint32_t> possilbe_divisors(size);
  std::iota(possilbe_divisors.begin(), possilbe_divisors.end(), 2);
  for (auto const i : possilbe_divisors) {
    if (!IsDivisibleBy(n, i))
      return false;
  }
  return true;
}

bool IsWilsonPrime(std::uint32_t n) {
  // Check if n is a prime number
  if (!IsPrime(n))
    return false;

  // res = (P - 1)! mod (P * P)
  std::int64_t min_size{0};
  std::vector<std::uint64_t> v(
      std::max(min_size, static_cast<std::int64_t>(n) - 1));
  std::iota(v.begin(), v.end(), 1);
  std::uint64_t divisor =
      static_cast<std::uint64_t>(n) * static_cast<std::uint64_t>(n);
  auto res = std::accumulate(v.cbegin(), v.cend(), 1,
                             [divisor](std::uint64_t lhs, std::uint64_t rhs) {
                               return (lhs * rhs) % divisor;
                             });
  return res + 1U == divisor;
}