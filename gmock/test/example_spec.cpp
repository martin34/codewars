#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>

using namespace testing;

class MyOptional;
class ParameterServer
{
  public:
    virtual void SetValue(std::string key, bool value);
    virtual bool GetValue(std::string key);
    virtual MyOptional GetValueIfAvailable(std::string key);
    virtual ~ParameterServer();
};

class MyOptional{
  public:
    MyOptional() = default;
    MyOptional(bool value) : value_(value), value_set_(true){}

    bool GetValue() const {return value_;}
    bool IsSet() const {return value_set_;}

  private:
    bool value_{};
    bool value_set_{false};
};
bool operator==(MyOptional const& lhs, MyOptional const& rhs){
  bool equal{};
  if(lhs.IsSet() && rhs.IsSet())
  {
    equal = lhs.GetValue() == rhs.GetValue();
  }
  else{
    equal = lhs.IsSet() == rhs.IsSet();
  }
  return equal; 
}
std::ostream& operator<<(std::ostream& output_stream, MyOptional const& type){
  if(type.IsSet()) 
  {
    output_stream << "Optional is set with value: " << type.GetValue();
  }
  else{
    output_stream << "Optional is not set";
  }
  return output_stream;
}

class MockParameterServer
{
  public:
    MOCK_METHOD2(SetValue, void(std::string, bool));
    MOCK_METHOD1(GetValue, bool(std::string));
    MOCK_METHOD1(GetValueIfAvailable, MyOptional(std::string));
};


TEST(GMockExampleSpec, CheckForMethodCall)
{
  MockParameterServer server;
  EXPECT_CALL(server, SetValue(Eq("parameter_foo"), Eq(true))).Times(1);
  server.SetValue("parameter_foo", true);
}

TEST(GMockExampleSpec, CheckForReturnValue)
{
  MockParameterServer server;
  EXPECT_CALL(server, GetValue(Eq("parameter_foo"))).WillRepeatedly(Return(true));
  EXPECT_TRUE(server.GetValue("parameter_foo"));
}

TEST(GMockExampleSpec, CheckForException)
{
  MockParameterServer server;
  EXPECT_CALL(server, GetValue(Eq("parameter_foo"))).WillRepeatedly(Throw(std::runtime_error("bla")));
  EXPECT_THROW(server.GetValue("parameter_foo"), std::runtime_error);
}

TEST(GMockExampleSpec, CheckForCustomType)
{
  MockParameterServer server;
  EXPECT_CALL(server, GetValueIfAvailable(("parameter_foo"))).Times(1).WillRepeatedly(Return(MyOptional{true}));
  EXPECT_THAT(server.GetValueIfAvailable("parameter_foo"), Eq(MyOptional{true}));
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
