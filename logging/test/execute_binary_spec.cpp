#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <string>

namespace {
using namespace ::testing;

TEST(ExecuteBinarySpec, WhenTypical) {
  const char *path = "./logging/test/test_binary";
  char path_[] = "./logging/test/test_binary";
  char *const argv[] = {path_, nullptr};
  auto result = execv(path, argv);
  EXPECT_THAT(result, Eq(0));
}

} // namespace