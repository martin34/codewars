#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>

namespace {

using namespace ::testing;

class Proxy {
public:
  void SetA(bool a) { a_ = a; }
  void SetB(int b) { b_ = b; }
  void SetC(double c) { c_ = c; }
  void SetD(std::string d) { d_ = d; }
  bool IsAspectX() const { return a_ && (c_ > b_); }
  bool IsAspectY() const { return DContains("foo") && (c_ > b_); }
  bool IsAspectZ() const { return DContains("bar") && a_; }

private:
  bool DContains(const std::string &v) const {
    return d_.find(v) != std::string::npos;
  }
  bool a_{};
  int b_{};
  double c_{};
  std::string d_{};
};

struct Params {
  bool a;
  int b;
  double c;
  std::string d;
  bool aspect_x;
  bool aspect_y;
  bool aspect_z;
};
class ParamsBuilder {
public:
  Params Build() { return params_; }
  ParamsBuilder &WithA(bool a) {
    params_.a = a;
    return *this;
  }
  ParamsBuilder &WithB(int b) {
    params_.b = b;
    return *this;
  }
  ParamsBuilder &WithC(double c) {
    params_.c = c;
    return *this;
  }
  ParamsBuilder &WithD(const std::string &d) {
    params_.d = d;
    return *this;
  }
  ParamsBuilder &ExpectX(bool x) {
    params_.aspect_x = x;
    return *this;
  }
  ParamsBuilder &ExpectY(bool y) {
    params_.aspect_y = y;
    return *this;
  }
  ParamsBuilder &ExpectZ(bool z) {
    params_.aspect_z = z;
    return *this;
  }

private:
  Params params_;
};

class OtherTestFixture : public testing::TestWithParam<Params> {
public:
  OtherTestFixture() {
    unit.SetA(GetParam().a);
    unit.SetB(GetParam().b);
    unit.SetC(GetParam().c);
    unit.SetD(GetParam().d);
  }
  Proxy unit{};
};

TEST_P(OtherTestFixture, Aspects) {
  EXPECT_THAT(unit.IsAspectX(), Eq(GetParam().aspect_x));
  EXPECT_THAT(unit.IsAspectY(), Eq(GetParam().aspect_y));
  EXPECT_THAT(unit.IsAspectZ(), Eq(GetParam().aspect_z));
}

INSTANTIATE_TEST_SUITE_P(Foo, OtherTestFixture,
                         Values(
                             // clang-format off
    ParamsBuilder().WithA(true).WithB(1).WithC(5.).ExpectX(true).ExpectY(false).ExpectZ(false).Build(),
    ParamsBuilder().WithA(false).WithB(1).WithC(5.).ExpectX(false).ExpectY(false).ExpectZ(false).Build(),
    ParamsBuilder().WithA(true).WithB(5).WithC(1.).ExpectX(false).ExpectY(false).ExpectZ(false).Build(),
    ParamsBuilder().WithA(true).WithD("bar").ExpectX(false).ExpectY(false).ExpectZ(true).Build(),
    ParamsBuilder().WithA(true).WithD("BAR").ExpectX(false).ExpectY(false).ExpectZ(false).Build(),
    ParamsBuilder().WithB(1).WithC(5.).WithD("foo").ExpectX(false).ExpectY(true).ExpectZ(false).Build(),
    ParamsBuilder().WithB(1).WithC(5.).WithD("FOO").ExpectX(false).ExpectY(false).ExpectZ(false).Build(),
    ParamsBuilder().WithB(5).WithC(1.).WithD("foo").ExpectX(false).ExpectY(false).ExpectZ(false).Build(),
    ParamsBuilder().WithA(true).WithB(1).WithC(5.).WithD("bar").ExpectX(true).ExpectY(false).ExpectZ(true).Build(),
    ParamsBuilder().WithA(true).WithB(1).WithC(5.).WithD("foobar").ExpectX(true).ExpectY(true).ExpectZ(true).Build()
                             // clang-format on 
    ));


class YetOtherTestFixture : public testing::TestWithParam<Params> {
public:
  YetOtherTestFixture() {
    unit.SetA(GetParam().a);
    unit.SetB(GetParam().b);
    unit.SetC(GetParam().c);
    unit.SetD(GetParam().d);
  }
  Proxy unit{};
};
TEST_P(YetOtherTestFixture, Aspects) {
  EXPECT_THAT(unit.IsAspectX(), Eq(GetParam().aspect_x));
  EXPECT_THAT(unit.IsAspectY(), Eq(GetParam().aspect_y));
  EXPECT_THAT(unit.IsAspectZ(), Eq(GetParam().aspect_z));
}

using ModifyFunc = std::function<void(Params&)>;
class Modifier{
  public:
    Modifier(Params params) : params_(params){}
    Modifier& Modify(ModifyFunc&& func)
    {
      func(params_);
      return *this;
    }
    Params Build(){
      return params_;
    }
  private:
    Params params_;
};
INSTANTIATE_TEST_SUITE_P(Foo, YetOtherTestFixture,
                         Values(
                             // clang-format off
                           Modifier(Params{}).Modify([](Params& p){p.b = 5;}).Build(),
                           Modifier(Params{}).Modify([](Params& p){p.a = true;}).Modify([](Params& p){p.d = "bar";}).Modify([](Params& p){p.aspect_z = true;}).Build()
                             // clang-format on 
                           ));

} // namespace