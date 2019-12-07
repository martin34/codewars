
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>

#include "builder/builder.h"

namespace {
using namespace ::testing;

class PartA : public IPart {
public:
  virtual void Do(){};
  virtual ~PartA() = default;
};

TEST(Builder, AddPart) {
  Builder unit{};
  unit.AddPart<PartA>();

  EXPECT_NO_THROW(unit.Build());
}
class PartB : public IPart {
public:
  virtual void Do(){};
  virtual ~PartB() = default;
};
TEST(Builder, AddMultipleParts) {
  Builder unit{};
  unit.AddPart<PartA>();
  unit.AddPart<PartB>();

  EXPECT_NO_THROW(unit.Build());
}
} // namespace