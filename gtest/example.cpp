#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

using namespace ::testing;

class Proxy {
public:
  void SetA(int i) { i_ = i; }
  void SetB(int s) { s_ = s; }

  int GetSum() const { return i_ + s_; }
  int GetDifference() const { return i_ - s_; }

private:
  int i_{};
  int s_{};
};

class TestFixture
    : public testing::TestWithParam<std::tuple<int, int, int, int>> {};

TEST_P(TestFixture, GetSum) {
  Proxy unit{};
  int a, b, sum, diff;
  std::tie(a, b, sum, diff) = GetParam();
  unit.SetA(a);
  unit.SetB(b);
  EXPECT_THAT(sum, unit.GetSum());
  EXPECT_THAT(diff, unit.GetDifference());
}

INSTANTIATE_TEST_SUITE_P(Foo, TestFixture,
                         Values(std::make_tuple(0, 0, 0, 0),
                                std::make_tuple(1, 1, 2, 0)));

} // namespace