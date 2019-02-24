#include <cstdint>
#include <memory>
#include <functional>

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


class SubscriberImp;
class Subscriber{
  public:
    using Callback = std::function<void(std::int32_t)>;
    Subscriber(std::weak_ptr<IPublisher> publisher, Callback callback); 

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
