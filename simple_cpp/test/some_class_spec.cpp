#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "simple_cpp/some_class.h"

using namespace ::testing;

TEST(Parent, WhenTypical) {
  Parent unit;
  EXPECT_THAT(unit.ReturnANumber(), Eq(kParent));
  EXPECT_THAT(unit.ReturnANumberFoo(), Eq(kParent));
}

TEST(Child, WhenTypical) {
  Child unit;
  EXPECT_THAT(unit.ReturnANumber(), Eq(kChild));
  EXPECT_THAT(unit.ReturnANumberFoo(), Eq(kChild));
}

TEST(Child, WhenUsingParentPointer) {
  std::unique_ptr<Parent> unit = std::make_unique<Child>();
  EXPECT_THAT(unit->ReturnANumber(), Eq(kChild));
  EXPECT_THAT(unit->ReturnANumberFoo(), Eq(kChild));
}

TEST(Child, WhenUsingParentReference) {
  Child unit;
  Parent &ref_unit = unit;
  EXPECT_THAT(ref_unit.ReturnANumber(), Eq(kChild));
  EXPECT_THAT(unit.ReturnANumberFoo(), Eq(kChild));
}
