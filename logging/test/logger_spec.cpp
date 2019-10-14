#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "logging/logger.h"

namespace {
using namespace ::testing;

class LoggerMock : public logging::Logger {
public:
  MOCK_METHOD1(LogError, void(std::string const &));
};

// Order matters, because of static member
TEST(Logger, WhenNoLoggerSet) {
  EXPECT_THROW(logging::Logger::GetLogger(), std::runtime_error);
}
TEST(Logger, WhenLogError) {
  LoggerMock global_logger;
  logging::Logger::SetLogger(global_logger);
  auto &logger = logging::Logger::GetLogger();
  std::string msg{"FooBar"};

  EXPECT_CALL(global_logger, LogError(msg)).Times(1);

  logger.LogError(msg);
}
} // namespace