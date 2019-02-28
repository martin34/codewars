#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "pub_sub/src/pub_sub.h"
#include "pub_sub/test/fixture.h"

using namespace testing;

TEST_F(PubSubSpecFixtureInt32, WhenSendingInt)
{
  Init();
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixtureInt32, WhenSendingIntCreateSubcriberAfterPublisher)
{
  Init();
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber{port, callback_};
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixtureInt32, WhenMovingSubsciber)
{
  Init();
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber2(std::move(subscriber));
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_, Eq(3));
}
TEST_F(PubSubSpecFixtureInt32, WhenCopyingSubsciber)
{
  Init();
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
TEST_F(PubSubSpecFixtureInt32, WhenCopyAssignmentOfSubsciber)
{
  Init();
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
TEST_F(PubSubSpecFixtureInt32, WhenSubscriberDestructedBeforeSend)
{
  Init();
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  {
    Subscriber subscriber{port, callback_};
  }
  publisher->Send(3);
  ASSERT_THAT(received_data_, Eq(false));
}
TEST_F(PubSubSpecFixtureInt32, WhenBindSubscriberToNotExistingPublisher)
{
  Init();
  Port port_sub{1};
  Subscriber subscriber{port_sub, callback_};
  Port port_pub{2};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port_pub);
}
/* TEST_F(PubSubSpecFixtureData, WhenSendingStruct) */
/* { */
/*   Port port{1}; */
/*   Subscriber subscriber{port, callback_}; */
/*   std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port); */
/*   Data data{1}; */
/*   publisher->Send(data); */
/*   ASSERT_THAT(received_data_, Eq(true)); */
/*   EXPECT_THAT(actual_data_, Eq(data)); */
/* } */
// Only currently it is not possible to have more than one Subscriber
