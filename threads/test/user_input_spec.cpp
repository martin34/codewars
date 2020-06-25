#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

#include <boost/process.hpp>

namespace {
using namespace ::testing;

std::vector<std::string> exec(const char *cmd, const std::string &stdin) {
  boost::process::ipstream pipe_stream;
  boost::process::opstream in;

  boost::process::child c{cmd, boost::process::std_out > pipe_stream,
                          boost::process::std_in < in};

  in << stdin << std::endl;

  std::vector<std::string> lines{};

  std::string line{};
  if (pipe_stream && std::getline(pipe_stream, line) && !line.empty()) {
    lines.push_back(line);
  }

  c.terminate();
  return lines;
}

TEST(Multiprocess, CheckStdout) {
  const char *path{"./threads/user_input"};
  auto actual = exec(path, "");

  EXPECT_THAT(actual, Contains(std::string{"Foo"}));
}
TEST(Multiprocess, ReactOnStdinWhenBar) {
  const char *path{"./threads/user_input --stdin2stdout Bar"};
  auto actual = exec(path, "Bar");

  EXPECT_THAT(actual, Contains(std::string{"Bar"}));
}
TEST(Multiprocess, ReactOnStdinWhenBlub) {
  const char *path{"./threads/user_input --stdin2stdout"};
  auto actual = exec(path, "Blub");

  EXPECT_THAT(actual, Contains(std::string{"Blub"}));
}
} // namespace
