#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/process.hpp>

namespace {
using namespace ::testing;

std::vector<std::string> exec(const char *cmd) {
  boost::process::ipstream pipe_stream;
  boost::process::child c{cmd, boost::process::std_out > pipe_stream};

  std::vector<std::string> lines{};

  std::string line{};
  while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()) {
    lines.push_back(line);
  }

  return lines;
}

TEST(Foo, Bar) {
  const char *path{"./threads/user_input"};
  auto actual = exec(path);

  EXPECT_THAT(actual, Contains(std::string{"Foo"}));
}

} // namespace
