#include <bitset>
#include <cstddef>
#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

enum class Bits { Zero, One, Two, Size };

template <typename T> class Mask {
public:
  Mask() = default;
  explicit Mask(std::uint32_t bits) : mask_{bits} {}

  explicit Mask(T bit) { Set(bit, true); }
  template <typename... Ts> explicit Mask(T bit, Ts... bits) : Mask(bits...) {
    Set(bit, true);
  }

  bool IsSet(T bit) const { return mask_[static_cast<std::size_t>(bit)]; }
  void Set(T bit, bool value) {
    mask_.set(static_cast<std::size_t>(bit), value);
  }

  Mask<T> &operator|=(const Mask<T> &rhs) {
    mask_ |= rhs.mask_;
    return *this;
  }

  unsigned long ToULong() const { return mask_.to_ulong(); }

private:
  std::bitset<static_cast<std::size_t>(Bits::Size)> mask_{};
};

template <typename T> Mask<T> operator|(Mask<T> lhs, const Mask<T> &rhs) {
  lhs |= rhs;
  return lhs;
}

TEST(Mask, IsSet) {
  Mask<Bits> mask{0b101};
  EXPECT_TRUE(mask.IsSet(Bits::Zero));
  EXPECT_FALSE(mask.IsSet(Bits::One));
  EXPECT_TRUE(mask.IsSet(Bits::Two));
}
TEST(Mask, Set) {
  Mask<Bits> mask{0b101};
  mask.Set(Bits::One, true);
  EXPECT_TRUE(mask.IsSet(Bits::One));
}
TEST(Mask, Operator) {
  Mask<Bits> lhs{0b101};
  Mask<Bits> rhs{0b010};
  lhs |= rhs;
  EXPECT_TRUE(lhs.IsSet(Bits::One));
}
TEST(Mask, OperatorTwo) {
  Mask<Bits> lhs{0b101};
  Mask<Bits> rhs{0b010};
  const auto result = lhs | rhs;
  EXPECT_TRUE(result.IsSet(Bits::One));
}
TEST(Mask, OrWithBits) {
  Mask<Bits> lhs{Bits::One};
  Mask<Bits> rhs{Bits::Two};
  const auto result = lhs | rhs;
  EXPECT_THAT(result.ToULong(), ::testing::Eq(0b110));
}
TEST(Mask, Const) {
  Mask<Bits> mask{Bits::Zero};
  EXPECT_THAT(mask.ToULong(), ::testing::Eq(0b1));
}
TEST(Mask, ConstTwo) {
  Mask<Bits> mask{Bits::Zero, Bits::One};
  EXPECT_THAT(mask.ToULong(), ::testing::Eq(0b11));
}
TEST(Mask, ConstThree) {
  Mask<Bits> mask{Bits::Zero, Bits::Two, Bits::One};
  EXPECT_THAT(mask.ToULong(), ::testing::Eq(0b111));
}
enum class Other { Foo };
// Does not compile
// TEST(Mask, WrongUsage) {
//   Mask<Bits> mask{Bits::Zero, Other::Foo, Bits::One};
// }
} // namespace
