#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "logging/logger.h"

#include <chrono>
#include <thread>

namespace {
using namespace ::testing;
using ::testing::InSequence;
using namespace std::literals::chrono_literals;

class LoggerMock : public logging::Logger {
public:
  MOCK_METHOD1(LogErrorImpl, void(std::string const &));
};

// Order matters, because of static member
TEST(Logger, WhenNoLoggerSet) {
  EXPECT_THROW(logging::Logger::GetLogger(), std::runtime_error);
}
class LoggerFixture : public ::Test {
public:
  LoggerFixture() { logging::Logger::SetLogger(mock); };

  LoggerMock mock{};
};
TEST_F(LoggerFixture, WhenLogError) {
  std::string msg{"FooBar"};

  EXPECT_CALL(mock, LogErrorImpl(msg)).Times(1);

  auto &logger = logging::Logger::GetLogger();
  logger.LogError(msg);
}
TEST_F(LoggerFixture, WhenMultipleTimeLogError) {
  std::string msg1{"1"};
  std::string msg2{"2"};
  {
    InSequence sequence;
    EXPECT_CALL(mock, LogErrorImpl(msg1)).Times(1);
    EXPECT_CALL(mock, LogErrorImpl(msg2)).Times(1);
  }

  auto &logger = logging::Logger::GetLogger();

  logger.LogError(msg1);
  logger.LogError(msg2);
}
TEST_F(LoggerFixture, WhenMultipleThreads) {
  std::string msg1{"1"};
  std::string msg2{"2"};

  EXPECT_CALL(mock, LogErrorImpl(msg1)).Times(1);
  EXPECT_CALL(mock, LogErrorImpl(msg2)).Times(1);

  std::thread t1([msg1]() {
    auto &logger = logging::Logger::GetLogger();
    logger.LogError(msg1);
  });
  std::thread t2([msg2]() {
    auto &logger = logging::Logger::GetLogger();
    logger.LogError(msg2);
  });
  t1.join();
  t2.join();
}
void Sleep() { std::this_thread::sleep_for(1s); }
TEST_F(LoggerFixture, WhenMultipleThreadsSlowLogger) {
  std::string msg1{"1"};
  std::string msg2{"2"};

  EXPECT_CALL(mock, LogErrorImpl(msg1))
      .Times(5)
      .WillRepeatedly(InvokeWithoutArgs(Sleep));
  EXPECT_CALL(mock, LogErrorImpl(msg2))
      .Times(4)
      .WillRepeatedly(InvokeWithoutArgs(Sleep));

  std::thread t1([msg1]() {
    auto &logger = logging::Logger::GetLogger();
    logger.LogError(msg1);
    logger.LogError(msg1);
    logger.LogError(msg1);
    logger.LogError(msg1);
    logger.LogError(msg1);
  });
  std::thread t2([msg2]() {
    auto &logger = logging::Logger::GetLogger();
    logger.LogError(msg2);
    logger.LogError(msg2);
    logger.LogError(msg2);
    logger.LogError(msg2);
  });
  t1.join();
  t2.join();
}
} // namespace