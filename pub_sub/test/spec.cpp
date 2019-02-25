#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "pub_sub/src/pub_sub.h"

using namespace testing;

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
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenSendingIntCreateSubcriberAfterPublisher)
{
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber{port, callback_};
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenMovingSubsciber)
{
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber2(std::move(subscriber));
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenCopyingSubsciber)
{
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2(subscriber);
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenCopyAssignmentOfSubsciber)
{
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2=subscriber;
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixture, WhenSubscriberDestructedBeforeSend)
{
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  {
    Subscriber subscriber{port, callback_};
  }
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(false));
}
TEST_F(PubSubSpecFixture, WhenBindSubscriberToNotExistingPublisher)
{
  Port port_sub{1};
  Subscriber subscriber{port_sub, callback_};
  Port port_pub{2};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port_pub);
}

// Only currently it is not possible to have more than one Subscriber
