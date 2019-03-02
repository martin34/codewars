#ifndef  PUB_SUB_TEST_FIXTURE_H_
#define  PUB_SUB_TEST_FIXTURE_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "pub_sub/src/pub_sub.h"

using namespace testing;

class IntSerializer : public Serializable{
  public:
    IntSerializer() = default;
    IntSerializer(std::int32_t data) : data_{data}{}
    IntSerializer(IntSerializer const& parent) : data_(parent.Get()){}
    IntSerializer operator=(IntSerializer const& parent){
      this->data_ = parent.Get();
      return *this;}
    std::int32_t Get() const{
      return data_;
    }
  private:
      std::int32_t data_{};
};
struct Data{
  std::int32_t member_one;
};
bool operator==(Data const& lhs, Data const& rhs)
{
  return lhs.member_one == rhs.member_one;
}
class DataSerializer : public Serializable{
  public:
    DataSerializer() = default;
    DataSerializer(Data data) : data_{data}{}
    DataSerializer(DataSerializer const& parent) : data_(parent.Get()){}
    DataSerializer operator=(DataSerializer const& parent){
      this->data_ = parent.Get();
      return *this;}
    DataSerializer* Clone(){return this;}
    Data Get() const{
      return data_;
    }
  private:
      Data data_{};
};


template<typename SerializerType>
class PubSubSpecFixture : public Test{
  protected:
    using TypedCallback = std::function<void(SerializerType)>;
    SerializerType actual_data_{};
    bool received_data_{false};
    void TypedInit(){
      typed_callback_ = TypedCallback{[this](SerializerType data){
        received_data_ = true;
        actual_data_ = data;
      }};
    }
    TypedCallback typed_callback_{[](SerializerType data){}};
};
using PubSubSpecFixtureInt32 = PubSubSpecFixture<IntSerializer>;
using PubSubSpecFixtureData = PubSubSpecFixture<DataSerializer>;
#endif //  PUB_SUB_TEST_FIXTURE_H_
