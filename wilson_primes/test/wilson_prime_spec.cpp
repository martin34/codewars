#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <numeric>

#include "wilson_primes/src/wilson_prime.h"

using namespace ::testing;

class IsPrimeSpecWhenTrue : public TestWithParam<int> {};
TEST_P(IsPrimeSpecWhenTrue, WhenTrue) {
  EXPECT_THAT(v1::IsPrime(GetParam()), Eq(true));
}
INSTANTIATE_TEST_CASE_P(WhenTrue, IsPrimeSpecWhenTrue,
                        Values(2, 3, 5, 7, 11, 13));
class IsPrimeSpecWhenFalse : public TestWithParam<int> {};
TEST_P(IsPrimeSpecWhenFalse, WhenTrue) {
  EXPECT_THAT(v1::IsPrime(GetParam()), Eq(false));
}
INSTANTIATE_TEST_CASE_P(WhenFalse, IsPrimeSpecWhenFalse,
                        Values(4, 6, 8, 9, 10, 12, 14, 15, 16));

TEST_P(IsPrimeSpecWhenTrue, v2_WhenTrue) {
  EXPECT_THAT(v2::IsPrime(GetParam()), Eq(true));
}
INSTANTIATE_TEST_CASE_P(v2_WhenTrue, IsPrimeSpecWhenTrue,
                        Values(2, 3, 5, 7, 11, 13));
TEST_P(IsPrimeSpecWhenFalse, v2_WhenTrue) {
  EXPECT_THAT(v2::IsPrime(GetParam()), Eq(false));
}
INSTANTIATE_TEST_CASE_P(v2_WhenFalse, IsPrimeSpecWhenFalse,
                        Values(4, 6, 8, 9, 10, 12, 14, 15, 16));

std::uint64_t Factorial(std::uint32_t n) {
  std::uint32_t min_size{0};
  std::vector<std::uint64_t> v(std::max(min_size, n));
  std::iota(v.begin(), v.end(), 1);
  return std::accumulate(v.cbegin(), v.cend(), 1,
                         std::multiplies<std::uint64_t>());
}
struct TestParams {
  std::uint32_t input;
  std::uint32_t expected;
};
class FactorialSpec : public TestWithParam<TestParams> {};
TEST_P(FactorialSpec, WhenTypical) {
  auto param = GetParam();
  EXPECT_THAT(Factorial(param.input), Eq(param.expected));
}
INSTANTIATE_TEST_CASE_P(WhenFalse, FactorialSpec,
                        Values(TestParams{0, 1}, TestParams{1, 1},
                               TestParams{2, 2}, TestParams{3, 6},
                               TestParams{4, 24}, TestParams{5, 120}));

class IsWilsonPrimeSpec : public TestWithParam<int> {};
TEST_P(IsWilsonPrimeSpec, WhenFalse) {
  EXPECT_THAT(IsWilsonPrime(GetParam()), Eq(false));
}
class IsWilsonPrimeSpecWhenTrue : public TestWithParam<int> {};
TEST_P(IsWilsonPrimeSpecWhenTrue, WhenTrue) {
  EXPECT_THAT(IsWilsonPrime(GetParam()), Eq(true));
}

INSTANTIATE_TEST_CASE_P(WhenFalse, IsWilsonPrimeSpec, Values(0, 1, 2, 3, 4));
INSTANTIATE_TEST_CASE_P(WhenFalse2, IsWilsonPrimeSpec, Range(6, 11));
INSTANTIATE_TEST_CASE_P(WhenTrue, IsWilsonPrimeSpecWhenTrue,
                        Values(5, 13, 563));
