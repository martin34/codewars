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
    using Callback = std::function<void(std::int32_t)>;
    SubscriberImp(std::weak_ptr<IPublisher> publisher) : publisher_(publisher){
    }
    void SetReceiveCallback(Callback callback){
      callback_ = callback;
    }

    void Receive(std::int32_t data) override{
      callback_(data);
    }
    void RegisterMe(std::weak_ptr<SubscriberImp> me){
      auto pub = publisher_.lock();
      if(pub)
      {
        pub->Register(me);
      }
    }
  private:
    std::weak_ptr<IPublisher> publisher_;
    Callback callback_{[](std::int32_t){}};
};

class Subscriber{
  public:
    using Callback = std::function<void(std::int32_t)>;
    Subscriber(std::weak_ptr<IPublisher> publisher, Callback callback) : impl(std::make_shared<SubscriberImp>(publisher)){
      impl->RegisterMe(impl);
      impl->SetReceiveCallback(callback);
    }

  private:
    std::shared_ptr<SubscriberImp> impl; // Created once and pointer passed around, when instance of this is copied or moved.
};

class Publisher : public IPublisher{
  public:
    void Send(std::int32_t data)override{
      auto instance = subscriber_.lock();
      if(instance)
      {
        instance->Receive(data);
      }
    }
    void Register(std::weak_ptr<ISubscriber> subscriber)override{
      subscriber_ = subscriber;
    } 
  private:
    std::weak_ptr<ISubscriber> subscriber_;
};

class PubSubSpecFixture : public Test{
  protected:
    std::int32_t actual_data_{};
    bool received_data_{false};
    Subscriber::Callback callback_{[this](std::int32_t data){
      received_data_ = true;
      actual_data_ = data;
    }};
};
TEST_F(PubSubSpecFixture, WhenSendingInt)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  Subscriber subscriber{publisher, callback_};
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenMovingSubsciber)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  Subscriber subscriber{publisher, callback_};
  Subscriber subscriber2(std::move(subscriber));
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenCopyingSubsciber)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  std::shared_ptr<Publisher> publisher2 = std::make_shared<Publisher>();
  Subscriber subscriber(publisher, callback_);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2(subscriber); 
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenCopyAssignmentOfSubsciber)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  std::shared_ptr<Publisher> publisher2 = std::make_shared<Publisher>();
  Subscriber subscriber(publisher, callback_);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2 = subscriber; 
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenSubscriberDestructedBeforeSend)
{
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>();
  {
    Subscriber subscriber(publisher, callback_);
  }
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(false));
}
TEST_F(PubSubSpecFixture, WhenBindSubscriberToNotExistingPublisher)
{
  std::shared_ptr<Publisher> publisher{nullptr};
  Subscriber subscriber(publisher, callback_);
}
