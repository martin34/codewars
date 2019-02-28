#ifndef  PUB_SUB_TEST_FIXTURE_H_
#define  PUB_SUB_TEST_FIXTURE_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "pub_sub/src/pub_sub.h"

using namespace testing;

template<typename T>
class PubSubSpecFixture : public Test{
  protected:
    T actual_data_{};
    bool received_data_{false};
    void Init(){
      callback_ = Subscriber::Callback{[this](T data){
            received_data_ = true;
            actual_data_ = data;
          }};
    }
    Subscriber::Callback callback_{[](T data){}};
};
using PubSubSpecFixtureInt32 = PubSubSpecFixture<std::int32_t>;
struct Data{
  std::int32_t member_one;
};
bool operator==(Data const& lhs, Data const& rhs)
{
  return lhs.member_one == rhs.member_one;
}
using PubSubSpecFixtureData = PubSubSpecFixture<Data>;
#endif //  PUB_SUB_TEST_FIXTURE_H_
