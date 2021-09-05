#include <bitset>
#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <type_traits>

namespace {

template <typename T> static std::uint32_t BitId() {
  static std::uint32_t count{0};
  return count++;
}

template <class T, class Bitset> struct Base {
  using ThisBitset = Bitset;
  explicit Base(bool value) : value{value} {}
  bool value;
  static const std::uint32_t bit;
  virtual ~Base() = default;
};
template <class T, class Bitset>
const std::uint32_t Base<T, Bitset>::bit{BitId<Bitset>()};

template <typename T, typename... Ts> struct NextType {
  using ThisBitset = typename T::ThisBitset;
};
template <typename... ArgTypes> std::uint32_t Encode(ArgTypes... args);
template <typename T, typename... ArgTypes>
std::uint32_t Encode(T t, ArgTypes... args) {
  static_assert(std::is_same<typename T::ThisBitset,
                             typename NextType<ArgTypes...>::ThisBitset>::value,
                "Only Bits with same Bitset can be encoded");
  std::uint32_t encoded{0};
  encoded |= static_cast<std::uint32_t>(t.value) << T::bit;
  return encoded + Encode(args...);
}
template <typename T> std::uint32_t Encode(T t) {
  return static_cast<std::uint32_t>(t.value) << T::bit;
}

template <typename... ArgTypes>
std::bitset<sizeof...(ArgTypes)> Encode2Bitset(ArgTypes... args) {
  const auto encoded = Encode(args...);
  return std::bitset<sizeof...(ArgTypes)>{encoded};
}

template <typename T> bool IsSet(std::uint32_t value) {
  return value & (1U << T::bit);
}

template <typename Bitset> std::string Explain(std::uint32_t) {
  static_assert(true, "never use this, write a instantiation for your Bitset");
  return "";
}

struct Bits {};
struct First : public Base<First, Bits> {
  using Base<First, Bits>::Base;
};
struct Second : public Base<Second, Bits> {
  using Base<Second, Bits>::Base;
};
template <> std::string Explain<Bits>(std::uint32_t bits) {
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
  EXPECT_THAT(Encode(a, b), ::testing::Eq(1U));
  EXPECT_THAT(Encode(First{false}, Second{true}), ::testing::Eq(2U));
  EXPECT_THAT(Encode(Second{true}, First{false}), ::testing::Eq(2U));
  EXPECT_THAT(Encode(First{true}, Second{true}), ::testing::Eq(3U));
}
TEST(Bits, Encode2Bitset) {
  First a{true};
  EXPECT_THAT(Encode2Bitset(First{true}, Second{true}).to_ulong(),
              ::testing::Eq(3U));
  EXPECT_THAT(Encode2Bitset(First{true}, Second{true}).all(),
              ::testing::Eq(true));
  EXPECT_THAT(Encode2Bitset(First{true}, Second{true}).size(),
              ::testing::Eq(2));
}
TEST(Bits, Explain) {
  EXPECT_THAT(Explain<Bits>(0b00U),
              ::testing::Eq(std::string{"not first and not second"}));
  EXPECT_THAT(Explain<Bits>(0b01U),
              ::testing::Eq(std::string{"first and not second"}));
  EXPECT_THAT(Explain<Bits>(0b10U),
              ::testing::Eq(std::string{"not first and second"}));
  EXPECT_THAT(Explain<Bits>(0b11U),
              ::testing::Eq(std::string{"first and second"}));
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
TEST(OtherBits, Encode) {
  EXPECT_THAT(Encode(One{false}, Two{false}), ::testing::Eq(0));
  EXPECT_THAT(Encode(One{true}, Two{false}), ::testing::Eq(1));
  EXPECT_THAT(Encode(One{true}, Two{false}, Three{true}), ::testing::Eq(5));
  EXPECT_THAT(Encode(One{true}, Two{true}, Three{true}), ::testing::Eq(7));
}
// Does not compile, because First and One are from different Bitsets
// TEST(OtherBits, EncodeNotMaching) {
//   EXPECT_THAT(Encode(One{false}, First{true}), ::testing::Eq(0));
// }

template <> std::string Explain<OtherBits>(std::uint32_t bits) {
  std::stringstream stream;
  if (not(IsSet<One>(bits))) {
    stream << "not ";
  }
  stream << "one and ";
  if (not(IsSet<Two>(bits))) {
    stream << "not ";
  }
  stream << "two and ";
  if (not(IsSet<Three>(bits))) {
    stream << "not ";
  }
  stream << "three";
  return stream.str();
}

TEST(OtherBits, Explain) {
  EXPECT_THAT(Explain<OtherBits>(0b00U),
              ::testing::Eq(std::string{"not one and not two and not three"}));
  EXPECT_THAT(Explain<OtherBits>(0b01U),
              ::testing::Eq(std::string{"one and not two and not three"}));
  EXPECT_THAT(Explain<OtherBits>(0b10U),
              ::testing::Eq(std::string{"not one and two and not three"}));
  EXPECT_THAT(Explain<OtherBits>(0b11U),
              ::testing::Eq(std::string{"one and two and not three"}));
}
} // namespace
