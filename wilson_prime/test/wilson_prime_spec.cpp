#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <numeric>

#include "wilson_prime/wilson_prime.h"

using namespace ::testing;

class IsPrimeSpecWhenTrue : public TestWithParam<std::uint32_t> {};
TEST_P(IsPrimeSpecWhenTrue, WhenTrue) {
  EXPECT_THAT(v1::IsPrime(GetParam()), Eq(true));
}
INSTANTIATE_TEST_SUITE_P(WhenTrue, IsPrimeSpecWhenTrue,
                         Values(2U, 3U, 5U, 7U, 11U, 13U));
class IsPrimeSpecWhenFalse : public TestWithParam<std::uint32_t> {};
TEST_P(IsPrimeSpecWhenFalse, WhenTrue) {
  EXPECT_THAT(v1::IsPrime(GetParam()), Eq(false));
}
INSTANTIATE_TEST_SUITE_P(WhenFalse, IsPrimeSpecWhenFalse,
                         Values(4U, 6U, 8U, 9U, 10U, 12U, 14U, 15U, 16U));

TEST_P(IsPrimeSpecWhenTrue, v2_WhenTrue) {
  EXPECT_THAT(v2::IsPrime(GetParam()), Eq(true));
}
INSTANTIATE_TEST_SUITE_P(v2_WhenTrue, IsPrimeSpecWhenTrue,
                         Values(2U, 3U, 5U, 7U, 11U, 13U));
TEST_P(IsPrimeSpecWhenFalse, v2_WhenTrue) {
  EXPECT_THAT(v2::IsPrime(GetParam()), Eq(false));
}
INSTANTIATE_TEST_SUITE_P(v2_WhenFalse, IsPrimeSpecWhenFalse,
                         Values(4U, 6U, 8U, 9U, 10U, 12U, 14U, 15U, 16U));

std::uint64_t Factorial(std::uint32_t n) {
  std::uint32_t min_size{0};
  std::vector<std::uint64_t> v(std::max(min_size, n));
  std::iota(v.begin(), v.end(), 1);
  return std::accumulate(v.cbegin(), v.cend(), 1U,
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
INSTANTIATE_TEST_SUITE_P(WhenFalse, FactorialSpec,
                         Values(TestParams{0U, 1U}, TestParams{1U, 1U},
                                TestParams{2U, 2U}, TestParams{3U, 6U},
                                TestParams{4U, 24U}, TestParams{5U, 120U}));

class IsWilsonPrimeSpec : public TestWithParam<std::uint32_t> {};
TEST_P(IsWilsonPrimeSpec, WhenFalse) {
  EXPECT_THAT(IsWilsonPrime(GetParam()), Eq(false));
}
class IsWilsonPrimeSpecWhenTrue : public TestWithParam<std::uint32_t> {};
TEST_P(IsWilsonPrimeSpecWhenTrue, WhenTrue) {
  EXPECT_THAT(IsWilsonPrime(GetParam()), Eq(true));
}

INSTANTIATE_TEST_SUITE_P(WhenFalse, IsWilsonPrimeSpec,
                         Values(0U, 1U, 2U, 3U, 4U));
INSTANTIATE_TEST_SUITE_P(WhenFalse2, IsWilsonPrimeSpec, Range(6U, 11U));
INSTANTIATE_TEST_SUITE_P(WhenTrue, IsWilsonPrimeSpecWhenTrue,
                         Values(5U, 13U, 563U));
