#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

class ISubscriber{
  public:
    virtual void Receive(std::int32_t data)=0;
    virtual ~ISubscriber(){}
};

class IPublisher{
  public:
    virtual void Send(std::int32_t data)=0;
    virtual ~IPublisher(){}
};

class SubscriberMock : public ISubscriber{
  public:
    MOCK_METHOD1(Receive, void(std::int32_t));
};

class Publisher : public IPublisher{
  public:
    Publisher(ISubscriber* subscriber) : subscriber_(*subscriber){}
    void Send(std::int32_t data)override{
      subscriber_.Receive(data);
    }

  private:
    ISubscriber& subscriber_;
};

TEST(a, b)
{
  SubscriberMock subscriber;
  Publisher publischer(&subscriber);
  EXPECT_CALL(subscriber, Receive(Eq(3))).Times(1);
  publischer.Send(3);
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
