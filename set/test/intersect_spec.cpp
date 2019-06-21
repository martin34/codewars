#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <vector>

#include "set/src/intersect.h"

using namespace ::testing;

using strings = std::vector<std::string>;

struct TestParameter
{
  strings first, second, expect;
};

class GetSortedElementsOfFirstInSecondSpec : public TestWithParam<TestParameter> {};

TEST_P(GetSortedElementsOfFirstInSecondSpec, WhenTrue)
{
  auto first = GetParam().first;
  auto second = GetParam().second;
  auto expect = GetParam().expect;
  auto res = GetSortedElementsOfFirstInSecond(first, second);
  EXPECT_THAT(res, Eq(expect));
}

INSTANTIATE_TEST_CASE_P(Foo, GetSortedElementsOfFirstInSecondSpec, Values(
      TestParameter{strings{"abc"}, strings{"abc"}, strings{"abc"}},
      TestParameter{strings{"abc"}, strings{}, strings{}},
      TestParameter{strings{}, strings{"abc"}, strings{}},
      TestParameter{strings{"abc", "def"}, strings{"abc"}, strings{"abc"}},
      TestParameter{strings{"abc", "def", "hij"}, strings{"abc", "hij"}, strings{"abc", "hij"}},
      TestParameter{strings{"hij", "def", "abc"}, strings{"hij", "abc"}, strings{"abc", "hij"}}
      ));

