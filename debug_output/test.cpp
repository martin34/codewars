#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace {

std::uint32_t Encode(bool a, bool b, bool c) {
  std::uint32_t bits{};
  bits |= static_cast<std::uint32_t>(a) << 0U;
  bits |= static_cast<std::uint32_t>(b) << 1U;
  bits |= static_cast<std::uint32_t>(c) << 2U;
  return bits;
}
std::string Explain(std::uint32_t bits) {
  std::stringstream stream;
  if (not(bits & 1U)) {
    stream << "not ";
  }
  stream << "a and ";
  if (not(bits & 2U)) {
    stream << "not ";
  }
  stream << "b and ";
  if (not(bits & 4U)) {
    stream << "not ";
  }
  stream << "c";
  return stream.str();
}

TEST(Bits, Encode) {
  EXPECT_THAT(Encode(false, false, false), 0U);
  EXPECT_THAT(Encode(true, false, false), 1U);
  EXPECT_THAT(Encode(false, true, false), 2U);
  EXPECT_THAT(Encode(false, false, true), 4U);
  EXPECT_THAT(Encode(true, false, true), 5U);
}
TEST(Bits, Explain) {
  EXPECT_THAT(Explain(3U), std::string{"a and b and not c"});
  EXPECT_THAT(Explain(4U), std::string{"not a and not b and c"});
}
} // namespace
