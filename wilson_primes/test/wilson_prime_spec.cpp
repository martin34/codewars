#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <numeric>
#include <algorithm>
#include <functional>

using namespace ::testing;

inline bool IsDivisibleBy(std::uint64_t dividend, std::uint64_t divisor)
{
  return dividend % divisor;
}

bool IsPrime(std::uint32_t n)
{
  std::int64_t min_size = 0;
  std::int64_t max_size{static_cast<std::int64_t>(n) - 3};
  std::size_t size = std::max(min_size, max_size);
  std::vector<std::uint32_t> possilbe_divisors(size);
  std::iota(possilbe_divisors.begin(), possilbe_divisors.end(), 2);
  for(auto const i : possilbe_divisors)
  {
    if(!IsDivisibleBy(n, i))
      return false;
  }
  return true;
}

class IsPrimeSpecWhenTrue : public TestWithParam<int> {};
TEST_P(IsPrimeSpecWhenTrue, WhenTrue)
{
  EXPECT_THAT(IsPrime(GetParam()), Eq(true));
}
INSTANTIATE_TEST_CASE_P(WhenTrue, IsPrimeSpecWhenTrue, Values(0, 1, 2, 3, 5, 7, 11, 13));
class IsPrimeSpecWhenFalse : public TestWithParam<int> {};
TEST_P(IsPrimeSpecWhenFalse, WhenTrue)
{
  EXPECT_THAT(IsPrime(GetParam()), Eq(false));
}
INSTANTIATE_TEST_CASE_P(WhenFalse, IsPrimeSpecWhenFalse, Values(4, 6, 8, 9, 10, 12, 14, 15, 16));

std::uint64_t Factorial(std::uint32_t n)
{
  std::uint32_t min_size{0};
  std::vector<std::uint64_t> v(std::max(min_size, n));
  std::iota(v.begin(), v.end(), 1);
  return std::accumulate(v.cbegin(), v.cend(), 1, std::multiplies<std::uint64_t>());
}
struct TestParams
{
  std::uint32_t input;
  std::uint32_t expected;
};
class FactorialSpec : public TestWithParam<TestParams> {};
TEST_P(FactorialSpec, WhenTypical)
{
  auto param = GetParam();
  EXPECT_THAT(Factorial(param.input), Eq(param.expected));
}
INSTANTIATE_TEST_CASE_P(WhenFalse, FactorialSpec, Values(TestParams{0, 1},
                                                         TestParams{1, 1},
                                                         TestParams{2, 2},
                                                         TestParams{3, 6},
                                                         TestParams{4, 24},
                                                         TestParams{5, 120}));




// P is a prime number
//   ((P-1)! + 1) mod (P * P) = 0
bool IsWilsonPrime(std::uint32_t n)
{
  // Check if n is a prime number
  if(!IsPrime(n))
    return false;

  // res = (P - 1)! mod (P * P)
  std::int64_t min_size{0};
  std::vector<std::uint64_t> v(std::max(min_size, static_cast<std::int64_t>(n) - 1));
  std::iota(v.begin(), v.end(), 1);
  std::uint64_t divisor = static_cast<std::uint64_t>(n) * static_cast<std::uint64_t>(n);
  auto res = std::accumulate(v.cbegin(), v.cend(), 1, [divisor](std::uint64_t lhs, std::uint64_t rhs){return (lhs * rhs) % divisor;});
  return res + 1 == divisor;
}

class IsWilsonPrimeSpec : public TestWithParam<int> {};
TEST_P(IsWilsonPrimeSpec, WhenFalse)
{
  EXPECT_THAT(IsWilsonPrime(GetParam()), Eq(false));
}
class IsWilsonPrimeSpecWhenTrue : public TestWithParam<int> {};
TEST_P(IsWilsonPrimeSpecWhenTrue, WhenTrue)
{
  EXPECT_THAT(IsWilsonPrime(GetParam()), Eq(true));
}

INSTANTIATE_TEST_CASE_P(WhenFalse, IsWilsonPrimeSpec, Values(0, 1, 2, 3, 4));
INSTANTIATE_TEST_CASE_P(WhenFalse2, IsWilsonPrimeSpec, Range(6, 11));
INSTANTIATE_TEST_CASE_P(WhenTrue, IsWilsonPrimeSpecWhenTrue, Values(5, 13, 563));
