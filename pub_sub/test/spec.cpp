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
