#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "threads/src/auto_join_thread.h"

using namespace std::literals::chrono_literals;
using namespace ::testing;

class Logger{
  public: 
    Logger(std::streambuf* output_stream) : output_stream_(output_stream){
      output_stream_ << "Created logger" << std::endl;
    };
    void Log(std::string const& msg){
      std::lock_guard<std::mutex> lock{mutex_};
      output_stream_ << msg;
      std::this_thread::sleep_for(2s);
      output_stream_ << std::endl;
    }
  private:
    std::ostream output_stream_;
    std::mutex mutex_;
};

TEST(Logging, WhenCreatedLogger)
{
  std::stringbuf output_stream;
  Logger logger{&output_stream};

  std::string output = output_stream.str();
  EXPECT_THAT(output, Eq(std::string{"Created logger\n"}));
}

TEST(Logging, WhenLog)
{
  std::stringbuf output_stream;
  Logger logger{&output_stream};

  logger.Log("Foo");

  std::string output = output_stream.str();
  EXPECT_THAT(output, Eq(std::string{"Created logger\nFoo\n"}));
}

void Log(Logger& logger, std::string const& msg)
{
  logger.Log(msg);
}

TEST(Logging, WhenMultipleThreadsLogSimulatneously)
{
  std::stringbuf output_stream;
  Logger logger{&output_stream};

  std::string msg{"Foo"};
  AutoJoinThread thread1{std::thread(Log, std::ref(logger), "Foo")};
  AutoJoinThread thread2{std::thread(Log, std::ref(logger), "Bar")};
  thread1.join();
  thread2.join();

  std::string output = output_stream.str();
  EXPECT_THAT(output, Eq(std::string{"Created logger\nFoo\nBar\n"}));
}
