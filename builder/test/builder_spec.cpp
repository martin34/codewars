
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>

#include "builder/builder.h"

namespace {
using namespace ::testing;

class PartAMock : public IPart {
public:
  MOCK_METHOD(void, Do, (), (override));
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
} // namespace