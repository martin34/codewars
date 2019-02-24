
#include "pub_sub.h"

class SubscriberImp : public ISubscriber{
  public:
    using Callback = std::function<void(std::int32_t)>;
    SubscriberImp(std::weak_ptr<IPublisher> publisher) : publisher_(publisher){
    }
    void SetReceiveCallback(Callback callback){
      callback_ = callback;
    }

    void Receive(std::int32_t data) override{
      callback_(data);
    }
    void RegisterMe(std::weak_ptr<SubscriberImp> me){
      auto pub = publisher_.lock();
      if(pub)
      {
        pub->Register(me);
      }
    }
  private:
    std::weak_ptr<IPublisher> publisher_;
    Callback callback_{[](std::int32_t){}};
};
Subscriber::Subscriber(std::weak_ptr<IPublisher> publisher, Callback callback)
  : impl(std::make_shared<SubscriberImp>(publisher)){
    impl->RegisterMe(impl);
    impl->SetReceiveCallback(callback);
  }
