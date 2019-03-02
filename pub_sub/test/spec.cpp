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
  std::int32_t data{3};
  IntSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32, WhenSendingIntCreateSubcriberAfterPublisher)
{
  Init();
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber{port, callback_};
  std::int32_t data{3};
  IntSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32, WhenMovingSubsciber)
{
  Init();
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber2(std::move(subscriber));
  std::int32_t data{3};
  IntSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
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
  std::int32_t data{3};
  IntSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
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
  std::int32_t data{3};
  IntSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32, WhenSubscriberDestructedBeforeSend)
{
  Init();
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  {
    Subscriber subscriber{port, callback_};
  }
  std::int32_t data{3};
  IntSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(false));
}
TEST_F(PubSubSpecFixtureInt32, WhenBindSubscriberToNotExistingPublisher)
{
  Init();
  Port port_sub{1};
  Subscriber subscriber{port_sub, callback_};
  Port port_pub{2};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port_pub);
  std::int32_t data{3};
  IntSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(false));
}
TEST_F(PubSubSpecFixtureData, WhenSendingStruct)
{
  Init();
  Port port{1};
  Subscriber subscriber{port, callback_};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Data data{1};
  DataSerializer data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
// Only currently it is not possible to have more than one Subscriber
