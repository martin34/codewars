#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace {

template <typename T> bool IsSet(std::uint32_t value) {
  return value & (1U << T::bit);
}

class Bit {
public:
  Bit(bool value, std::uint16_t bit) : value_{value}, bit_{bit} {}

  std::uint32_t Get() const {
    return static_cast<std::uint32_t>(value_) << bit_;
  }

  ~Bit() = default;

private:
  bool value_;
  std::uint16_t bit_{0U};
};

class A : public Bit {
public:
  A(bool value) : Bit(value, bit) {}

  static constexpr std::uint16_t bit{0U};
};
class B : public Bit {
public:
  B(bool a) : Bit{a, bit} {}
  static constexpr std::uint16_t bit{1U};
};
class C : public Bit {
public:
  C(bool a) : Bit{a, bit} {}
  static constexpr std::uint16_t bit{2U};
};

std::uint32_t Encode(A a, B b, C c) {
  std::uint32_t bits{};
  bits |= a.Get();
  bits |= b.Get();
  bits |= c.Get();
  return bits;
}
std::string Explain(std::uint32_t bits) {
  std::stringstream stream;
  if (not(IsSet<A>(bits))) {
    stream << "not ";
  }
  stream << "a and ";
  if (not(IsSet<B>(bits))) {
    stream << "not ";
  }
  stream << "b and ";
  if (not(IsSet<C>(bits))) {
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
