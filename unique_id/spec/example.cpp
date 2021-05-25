#include "unique_id//example.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {
using namespace ::testing;

class LoggerMock : public ILogger {
public:
  MOCK_METHOD1(Log, void(std::int32_t));
  MOCK_METHOD1(Log, void(const char *));
};
TEST(DerivedA, LogId) {
  LoggerMock mock{};
  DerivedA a{mock};
  EXPECT_CALL(mock, Log(Matcher<std::int32_t>(_)));
  EXPECT_CALL(mock, Log(Matcher<const char *>(_)));
  a.Do();
}
TEST(Id, PrimitiveTypes_WhenEqual) {
  EXPECT_EQ(Id<int>(), Id<int>());
  EXPECT_EQ(Id<double>(), Id<double>());
}
TEST(Id, PrimitiveTypes_WhenNotEqual) {
  EXPECT_NE(Id<double>(), Id<int>());
  EXPECT_NE(Id<float>(), Id<double>());
}
TEST(Id, PrimitiveTypesWithUsing) {
  using myint = int;
  EXPECT_EQ(Id<myint>(), Id<int>());
}
} // namespace
