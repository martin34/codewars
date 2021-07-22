#include "wilson_prime.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

bool IsPrime(std::uint32_t n) { return v1::IsPrime(n); }

namespace v1 {
bool IsPrime(std::uint32_t n) {
  std::int64_t min_size{0};
  std::int64_t max_size{static_cast<std::int64_t>(n) - 3};
  std::size_t size{static_cast<std::size_t>(std::max(min_size, max_size))};
  std::vector<std::uint32_t> possilbe_divisors(size);
  std::iota(possilbe_divisors.begin(), possilbe_divisors.end(), 2);
  for (auto const i : possilbe_divisors) {
    if (!IsDivisibleBy(n, i))
      return false;
  }
  return true;
}
} // namespace v1
namespace v2 {
/// From: https://www.geeksforgeeks.org/c-program-to-check-prime-number/
bool IsPrime(std::uint32_t n) {
  // Corner cases
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;

  // This is checked so that we can skip
  // middle five numbers in below loop
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (std::uint32_t i = 5; i * i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;

  return true;
}
} // namespace v2

bool IsWilsonPrime(std::uint32_t n) {
  // Check if n is a prime number
  if (!IsPrime(n))
    return false;

  // res = (P - 1)! mod (P * P)
  std::int64_t min_size{0};
  std::vector<std::uint64_t> v(static_cast<std::size_t>(
      std::max(min_size, static_cast<std::int64_t>(n) - 1)));
  std::iota(v.begin(), v.end(), 1);
  std::uint64_t divisor =
      static_cast<std::uint64_t>(n) * static_cast<std::uint64_t>(n);
  auto res = std::accumulate(v.cbegin(), v.cend(), std::uint64_t{1U},
                             [divisor](std::uint64_t lhs, std::uint64_t rhs) {
                               return (lhs * rhs) % divisor;
                             });
  return (res + 1U) == divisor;
}
