#ifndef PUB_SUB_TEST_FIXTURE_H_
#define PUB_SUB_TEST_FIXTURE_H_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "pub_sub/pub_sub.h"

using namespace testing;

struct Data {
  std::int32_t member_one;
};
bool operator==(Data const &lhs, Data const &rhs) {
  return lhs.member_one == rhs.member_one;
}

template <typename T> class Serializer : public Serializable {
public:
  Serializer() = default;
  Serializer(T data) : data_{data} {}
  Serializer(Serializer const &parent) : data_(parent.Get()) {}
  Serializer operator=(Serializer const &parent) {
    this->data_ = parent.Get();
    return *this;
  }
  T Get() const { return data_; }

private:
  T data_{};
};

template <typename SerializerType> class PubSubSpecFixture : public Test {
protected:
  using TypedCallback = std::function<void(SerializerType)>;
  SerializerType actual_data_{};
  bool received_data_{false};
  void TypedInit() {
    typed_callback_ = TypedCallback{[this](SerializerType data) {
      received_data_ = true;
      actual_data_ = data;
    }};
  }
  TypedCallback typed_callback_{[](SerializerType) {}};
};
using PubSubSpecFixtureInt32t = PubSubSpecFixture<Serializer<std::int32_t>>;
using PubSubSpecFixtureData = PubSubSpecFixture<Serializer<Data>>;
#endif //  PUB_SUB_TEST_FIXTURE_H_
