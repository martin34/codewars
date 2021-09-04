#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace {

template <typename T> static std::uint32_t BitId() {
  static std::uint32_t count{0};
  return count++;
}

template <class T, class Bitset> struct Base {
  explicit Base(bool value) : value{value} {}
  bool value;
  static const std::uint32_t bit;
  virtual ~Base() = default;
};
template <class T, class Bitset>
const std::uint32_t Base<T, Bitset>::bit{BitId<Bitset>()};
struct Bits {};
struct First : public Base<First, Bits> {
  using Base<First, Bits>::Base;
};
struct Second : public Base<Second, Bits> {
  using Base<Second, Bits>::Base;
};
std::uint32_t Encode(First f, Second s) {
  std::uint32_t res{0};
  res |= static_cast<std::uint32_t>(f.value) << First::bit;
  res |= static_cast<std::uint32_t>(s.value) << Second::bit;
  return res;
}
template <typename T> bool IsSet(std::uint32_t value) {
  return value & (1U << T::bit);
}
std::string Explain(std::uint32_t bits) {
  std::stringstream stream;
  if (not(IsSet<First>(bits))) {
    stream << "not ";
  }
  stream << "first and ";
  if (not(IsSet<Second>(bits))) {
    stream << "not ";
  }
  stream << "second";
  return stream.str();
}
TEST(Bits, Init) {
  EXPECT_THAT(First::bit, ::testing::Eq(0));
  EXPECT_THAT(Second::bit, ::testing::Eq(1));
}
TEST(Bits, Encode) {
  First a{true};
  Second b{false};
  EXPECT_THAT(Encode(a, b), ::testing::Eq(1));
  EXPECT_THAT(Encode(First{false}, Second{true}), ::testing::Eq(2));
  EXPECT_THAT(Encode(First{true}, Second{true}), ::testing::Eq(3));
}
TEST(Bits, Explain) {
  EXPECT_THAT(Explain(0b00U),
              ::testing::Eq(std::string{"not first and not second"}));
  EXPECT_THAT(Explain(0b01U),
              ::testing::Eq(std::string{"first and not second"}));
  EXPECT_THAT(Explain(0b10U),
              ::testing::Eq(std::string{"not first and second"}));
  EXPECT_THAT(Explain(0b11U), ::testing::Eq(std::string{"first and second"}));
}

struct OtherBits {};
struct One : public Base<One, OtherBits> {
  using Base<One, OtherBits>::Base;
};
struct Two : public Base<Two, OtherBits> {
  using Base<Two, OtherBits>::Base;
};
struct Three : public Base<Three, OtherBits> {
  using Base<Three, OtherBits>::Base;
};
TEST(OtherBits, Init) {
  EXPECT_THAT(One::bit, ::testing::Eq(0));
  EXPECT_THAT(Two::bit, ::testing::Eq(1));
  EXPECT_THAT(Three::bit, ::testing::Eq(2));
}
// TEST(OtherBits, Encode)
// {
//   EXPECT_THAT(Encode(One{true}, Two{false}, Three{false}), ::testing::Eq(0));
//   EXPECT_THAT(Encode(One{true}, Two{false}, Three{false}), ::testing::Eq(1));
//   EXPECT_THAT(Encode(One{true}, Two{true}, Three{true}), ::testing::Eq(5));
// }
} // namespace
