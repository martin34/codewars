
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>

#include "builder/builder.h"

namespace {
using namespace ::testing;

class ICoolString {
public:
  virtual std::string Get() = 0;
  virtual ~ICoolString() = default;
};

class PartAMock : public IPart {
public:
  MOCK_METHOD(void, Do, (), (override));
  void Set(ICoolString &provider) { provider_ = &provider; }

  // private:
  ICoolString *provider_{nullptr};
};

TEST(Builder, AddPart) {
  Builder unit{};
  unit.AddPart<PartAMock>();

  auto product = unit.Build();
  auto mock = dynamic_cast<PartAMock *>(product.GetParts().at(0).get());
  EXPECT_CALL(*mock, Do()).Times(1);
  product.Do();
}
class PartBMock : public IPart {
public:
  MOCK_METHOD(void, Do, (), (override));
};
TEST(Builder, AddMultipleParts) {
  Builder unit{};
  unit.AddPart<PartAMock>();
  unit.AddPart<PartBMock>();

  auto product = unit.Build();
  auto mock_a = dynamic_cast<PartAMock *>(product.GetParts().at(0).get());
  auto mock_b = dynamic_cast<PartBMock *>(product.GetParts().at(1).get());
  {
    InSequence Sequence;
    EXPECT_CALL(*mock_a, Do()).Times(1);
    EXPECT_CALL(*mock_b, Do()).Times(1);
  }
  product.Do();
}

class CoolStringMock : public ICoolString {
public:
  MOCK_METHOD(std::string, Get, (), (override));
};
TEST(Builder, AddPartWithProperty) {
  Builder unit{};

  CoolStringMock cool_string;
  //   unit.AddPart<PartAMock>().With(cool_string);
  unit.AddPart<PartAMock>(cool_string);

  auto product = unit.Build();
  auto mock = dynamic_cast<PartAMock *>(product.GetParts().at(0).get());
  EXPECT_CALL(*mock, Do()).Times(1).WillRepeatedly(Invoke([mock]() {
    mock->provider_->Get();
  }));
  EXPECT_CALL(cool_string, Get());
  product.Do();
}
} // namespace