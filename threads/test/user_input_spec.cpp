#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
using namespace ::testing;

// To also provide stdin to the child we can use fork and pipe:
// https://stackoverflow.com/questions/6743771/popen-alternative
// or even better a process managing library e. g.
// https://github.com/skystrife/procxx or boost::process
// https://www.boost.org/doc/libs/1_64_0/doc/html/process.html
std::string exec(const char *cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

TEST(Foo, Bar) {
  const char *path{"./threads/user_input"};
  auto actual = exec(path);

  std::cerr << "Got on stdin: " << actual;
  EXPECT_THAT(actual, Eq(std::string{"Foo\n"}));
}

} // namespace
