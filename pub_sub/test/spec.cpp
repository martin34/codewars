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
    virtual void Register(ISubscriber* subscriber)=0;
    virtual ~IPublisher(){}
};

class SimpleSubscriber : public ISubscriber{
  public:
    SimpleSubscriber(std::weak_ptr<IPublisher> publisher) : publisher_(publisher){
      RegisterMe();
    }
    SimpleSubscriber(SimpleSubscriber&& donator){
      this->publisher_ = donator.publisher_.lock();
      RegisterMe();
    }
    ~SimpleSubscriber()
    {
      // Implement unsubscribe
    }
    void Receive(std::int32_t data) override{
      data_ = data;
    }
  std::int32_t data_{};
  private:
    void RegisterMe(){
      if(publisher_.expired())
      {
        return;
      }
      auto pub = publisher_.lock();
      pub->Register(this);
    }
    std::weak_ptr<IPublisher> publisher_;
};

class Publisher : public IPublisher{
  public:
    void Send(std::int32_t data)override{
      subscriber_->Receive(data);
    }
    void Register(ISubscriber* subscriber)override{
      subscriber_ = subscriber;
    } 
  private:
    ISubscriber* subscriber_;
};

TEST(PubSubSpec, WhenSendingInt)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  SimpleSubscriber subscriber(publisher);
  publisher->Send(3);
  EXPECT_THAT(subscriber.data_, Eq(3));
}
TEST(PubSubSpec, WhenMovingSubsciber)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  SimpleSubscriber subscriber(publisher);
  SimpleSubscriber subscriber2(std::move(subscriber)); // Pointer in Publisher still points to old subscriber
  publisher->Send(3);
  EXPECT_THAT(subscriber2.data_, Eq(3));
}
TEST(PubSubSpec, DISABLED_WhenSubscriberDestructedBeforeSend)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  {
    SimpleSubscriber subscriber(publisher);
  }
  publisher->Send(3);
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
