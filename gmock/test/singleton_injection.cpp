#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
using namespace ::testing;

class Mock {
public:
  MOCK_METHOD0(Do, void());
};
class SingletonMock {
public:
  Mock *GetMock() { return mock_; }
  void SetMock(Mock *mock) { mock_ = mock; }

private:
  static Mock *mock_;
};
Mock *SingletonMock::mock_ = nullptr;

class App {
public:
  App() {
    SingletonMock singleton{};
    mock = singleton.GetMock();
  }
  void Do() { mock->Do(); }

private:
  Mock *mock;
};

class AFixture : public Test {
public:
  AFixture() { singleton.SetMock(new Mock()); }
  ~AFixture() { delete singleton.GetMock(); }

protected:
  SingletonMock singleton{};
};

TEST_F(AFixture, a) {
  App app{};
  EXPECT_CALL(*singleton.GetMock(), Do()).Times(1);
  app.Do();
}
TEST_F(AFixture, b) {
  App app{};
  EXPECT_CALL(*singleton.GetMock(), Do()).Times(2);
  app.Do();
  app.Do();
}
} // namespace