#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <numeric>
#include <algorithm>

using namespace ::testing;


bool IsPrime(std::uint32_t n)
{
  std::int64_t min_size = 0;
  std::int64_t max_size{static_cast<std::int64_t>(n) - 3};
  std::size_t size = std::max(min_size, max_size);
  std::vector<std::uint32_t> possilbe_divisors(size);
  std::iota(possilbe_divisors.begin(), possilbe_divisors.end(), 2);
  for(auto const i : possilbe_divisors)
  {
    if(!(n % i))
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


// P is a prime number
// ((P-1)! + 1) / (P * P)
bool IsWilsonPrime(std::uint32_t n)
{
  // Check if n is a prime number
  if(!IsPrime(n))
    return false;
  // Check if calc
  return false;
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

/* INSTANTIATE_TEST_CASE_P(WhenFalse, IsWilsonPrimeSpec, Range(1, 5)); */
/* INSTANTIATE_TEST_CASE_P(WhenFalse2, IsWilsonPrimeSpec, Range(6, 11)); */
/* INSTANTIATE_TEST_CASE_P(WhenTrue, IsWilsonPrimeSpecWhenTrue, Values(5, 11, 563)); */
