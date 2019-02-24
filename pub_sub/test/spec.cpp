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
    virtual void Register(std::weak_ptr<ISubscriber> subscriber)=0;
    virtual ~IPublisher(){}
};

class SubscriberImp : public ISubscriber{
  public:
    SubscriberImp(std::weak_ptr<IPublisher> publisher) : publisher_(publisher){
    }
    void Receive(std::int32_t data) override{
      data_ = data;
    }
    void RegisterMe(std::weak_ptr<SubscriberImp> me){
      if(publisher_.expired())
      {
        return;
      }
      auto pub = publisher_.lock();
      pub->Register(me);
    }
    std::int32_t data_{};
  private:
    std::weak_ptr<IPublisher> publisher_;
};

class Subscriber : public ISubscriber{
  public:
    Subscriber(std::weak_ptr<IPublisher> publisher) : impl(std::make_shared<SubscriberImp>(publisher)){
      impl->RegisterMe(impl);
    }
    void Receive(std::int32_t data){};

    std::shared_ptr<SubscriberImp> impl;
  private:
};

class Publisher : public IPublisher{
  public:
    void Send(std::int32_t data)override{
      if(!subscriber_.expired())
      {
        subscriber_.lock()->Receive(data);
      }
    }
    void Register(std::weak_ptr<ISubscriber> subscriber)override{
      subscriber_ = subscriber;
    } 
  private:
    std::weak_ptr<ISubscriber> subscriber_;
};

TEST(PubSubSpec, WhenSendingInt)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  Subscriber subscriber{publisher};
  publisher->Send(3);
  EXPECT_THAT(subscriber.impl->data_, Eq(3));
}
TEST(PubSubSpec, WhenMovingSubsciber)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  Subscriber subscriber(publisher);
  Subscriber subscriber2(std::move(subscriber));
  publisher->Send(3);
  EXPECT_THAT(subscriber2.impl->data_, Eq(3));
}
TEST(PubSubSpec, WhenCopyingSubsciber)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  std::shared_ptr<Publisher> publisher2 = std::make_shared<Publisher>();
  Subscriber subscriber(publisher);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2(subscriber); 
  publisher->Send(3);
  EXPECT_THAT(subscriber2.impl->data_, Eq(3));
}
TEST(PubSubSpec, WhenCopyAssignmentOfSubsciber)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  std::shared_ptr<Publisher> publisher2 = std::make_shared<Publisher>();
  Subscriber subscriber(publisher);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2 = subscriber; 
  publisher->Send(3);
  EXPECT_THAT(subscriber2.impl->data_, Eq(3));
}
TEST(PubSubSpec, WhenSubscriberDestructedBeforeSend)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  {
    Subscriber subscriber(publisher);
  }
  publisher->Send(3);
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
