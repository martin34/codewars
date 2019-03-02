#ifndef PUB_SUB_SRC_PUB_SUB_H_
#define PUB_SUB_SRC_PUB_SUB_H_

#include <cstdint>
#include <memory>
#include <functional>
#include <iostream>

class Serializable{
  public:
    virtual ~Serializable() = default;
};

class ISubscriber{
  public:
    virtual void Receive(Serializable* data)=0;
    virtual ~ISubscriber(){}
};

class IPublisher{
  public:
    virtual void Send(Serializable* data)=0;
    virtual void Register(std::weak_ptr<ISubscriber> subscriber)=0;
    virtual ~IPublisher(){}
};

using Port = std::int32_t;

template<typename T>
T GetConcreteType(Serializable* data)
{
  T* my_data{dynamic_cast<T*>(data)};
  if(my_data)
  {
    return *my_data;
  }
  else
  {
    std::cerr << "Expected type of subscriber does not match received data type" << std::endl;
    throw std::bad_cast();
  }
}
class SubscriberImp;
class Subscriber{
  public:
    using Callback = std::function<void(Serializable*)>;
    Subscriber(Port port) : port_{port} {
    }
    void InitializeImpl(Port port, Callback callback);
    template<typename T>
    void AddCallback(std::function<void(T)> callback){
      auto usercallback = [callback](Serializable* data){
        auto instance = GetConcreteType<T>(data);
        callback(instance);
      };
      InitializeImpl(port_, usercallback);
    }

  private:
    Port port_{};
    std::shared_ptr<SubscriberImp> impl; // Created once and pointer passed around, when instance of this is copied or moved.
};

class Publisher : public IPublisher{
  public:
    Publisher(Port port);
    void Send(Serializable* data)override;
    void Register(std::weak_ptr<ISubscriber> subscriber)override{
      subscriber_ = subscriber;
    } 
  private:
    Port port_{};
    std::weak_ptr<ISubscriber> subscriber_;
};
#endif // PUB_SUB_SRC_PUB_SUB_H_
