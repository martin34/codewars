#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "pub_sub/src/pub_sub.h"
#include "pub_sub/test/fixture.h"

using namespace testing;

TEST_F(PubSubSpecFixtureInt32t, WhenSendingInt)
{
  TypedInit();
  Port port{1};
  Subscriber subscriber{port};
  subscriber.AddCallback<Serializer<std::int32_t>>(typed_callback_);
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  std::int32_t data{3};
  Serializer<std::int32_t> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32t, WhenSendingIntCreateSubcriberAfterPublisher)
{
  TypedInit();
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber{port};
  subscriber.AddCallback<Serializer<std::int32_t>>(typed_callback_);
  std::int32_t data{3};
  Serializer<std::int32_t> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32t, WhenMovingSubsciber)
{
  TypedInit();
  Port port{1};
  Subscriber subscriber{port};
  subscriber.AddCallback<Serializer<std::int32_t>>(typed_callback_);
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Subscriber subscriber2(std::move(subscriber));
  std::int32_t data{3};
  Serializer<std::int32_t> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32t, WhenCopyingSubsciber)
{
  TypedInit();
  Port port{1};
  Subscriber subscriber{port};
  subscriber.AddCallback<Serializer<std::int32_t>>(typed_callback_);
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2(subscriber);
  std::int32_t data{3};
  Serializer<std::int32_t> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32t, WhenCopyAssignmentOfSubsciber)
{
  TypedInit();
  Port port{1};
  Subscriber subscriber{port};
  subscriber.AddCallback<Serializer<std::int32_t>>(typed_callback_);
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  // Both subscriber have a pointer to the same impl instance. 
  // This is ok, as long as it is not possible to change the impl state after creation e. g. direct to a different publisher.
  Subscriber subscriber2=subscriber;
  std::int32_t data{3};
  Serializer<std::int32_t> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureInt32t, WhenSubscriberDestructedBeforeSend)
{
  TypedInit();
  Port port{1};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  {
    Subscriber subscriber{port};
    subscriber.AddCallback<Serializer<std::int32_t>>(typed_callback_);
  }
  std::int32_t data{3};
  Serializer<std::int32_t> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(false));
}
TEST_F(PubSubSpecFixtureInt32t, WhenBindSubscriberToNotExistingPublisher)
{
  TypedInit();
  Port port_sub{1};
  Subscriber subscriber{port_sub};
  subscriber.AddCallback<Serializer<std::int32_t>>(typed_callback_);
  Port port_pub{2};
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port_pub);
  std::int32_t data{3};
  Serializer<std::int32_t> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(false));
}
TEST_F(PubSubSpecFixtureData, WhenSendingStruct)
{
  TypedInit();
  Port port{1};
  Subscriber subscriber{port};
  subscriber.AddCallback<Serializer<Data>>(typed_callback_);
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  Data data{1};
  Serializer<Data> data_wrapper{data};
  publisher->Send(&data_wrapper);
  ASSERT_THAT(received_data_, Eq(true));
  EXPECT_THAT(actual_data_.Get(), Eq(data));
}
TEST_F(PubSubSpecFixtureData, WhenTypeMissmatch)
{
  TypedInit();
  Port port{1};
  Subscriber subscriber{port};
  subscriber.AddCallback<Serializer<Data>>(typed_callback_);
  std::shared_ptr<Publisher> publisher = std::make_shared<Publisher>(port);
  std::int32_t data{1};
  Serializer<std::int32_t> data_wrapper{data};
  EXPECT_THROW(publisher->Send(&data_wrapper), std::bad_cast);
}
