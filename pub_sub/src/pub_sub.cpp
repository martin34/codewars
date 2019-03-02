
#include "pub_sub.h"
#include <map>

class Registry{
  public:
    static Registry& Get(){
      if(!registry_)
      {
        registry_ = std::make_unique<Registry>();
      }
      return *registry_;
    }
    std::weak_ptr<SubscriberImp> GetSubscriber(Port port){
      return subscriber_map_[port];
    }
    void Register(Port port, std::weak_ptr<SubscriberImp> subscriber)
    {
      subscriber_map_.clear();
      subscriber_map_.emplace(port, subscriber);
    }

  private:
    static std::unique_ptr<Registry> registry_;
    std::map<Port, std::weak_ptr<SubscriberImp>> subscriber_map_{};
};

std::unique_ptr<Registry> Registry::registry_;

class SubscriberImp : public ISubscriber{
  public:
    using Callback = std::function<void(Serializable*)>;
    void SetReceiveCallback(Callback callback){
      callback_ = callback;
    }

    void Receive(Serializable* data) override{
      callback_(data);
    }
  private:
    Callback callback_{[](Serializable*){}};
};
Subscriber::Subscriber(Port port, Callback callback)
  : port_{port}, impl(std::make_shared<SubscriberImp>())
{
    impl->SetReceiveCallback(callback);
    Registry::Get().Register(port, impl);
}

Publisher::Publisher(Port port) : port_{port}{}
void Publisher::Send(Serializable* data){
   auto sub = Registry::Get().GetSubscriber(port_);
    auto instance = sub.lock();
    if(instance)
    {
      instance->Receive(data);
    }
}
