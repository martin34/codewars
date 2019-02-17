#include "foo.h"
#include <thread>
#include <future>
#include <iostream>
#include <chrono>

using namespace std::literals::chrono_literals;

int add(int a, int b)
{
  std::cerr << "Add function called with a: " << a << " b: " << b << std::endl;
  std::this_thread::sleep_for(2s);
  return a + b;
}
class AutoJoinThread{
  public: 
    AutoJoinThread(std::thread&& thread) : thread_(std::move(thread)){}
    ~AutoJoinThread(){
      if(thread_.joinable())
      {
        thread_.join();
      }
    }
    void join(){
      thread_.join();
    }

  private:
    std::thread thread_;
};

class Adder{
  public:
    Adder(int a, int b){
      std::packaged_task<int(int, int)> task(add);
      result_ = std::make_unique<std::future<int>>(task.get_future());
      thread_ = std::make_unique<AutoJoinThread>(std::thread(std::move(task), a, b));
    }
    int Get(){
      thread_->join();
      return result_->get();
    }

  private:
    std::unique_ptr<std::future<int>> result_;
    std::unique_ptr<AutoJoinThread> thread_;
};

void Foo::Calc(int value, int value2){
  Adder adder(value2, value2);
  Adder adder2(value, value);

  auto add_result = adder2.Get();
  auto add_result2 = adder.Get();

  std::packaged_task<void(int, int)> task3([this](int a, int b){
      std::cerr << "Multiply thread started with a: " << a << " b: " << b << std::endl;
      std::this_thread::sleep_for(1s);
      value_ = a * b;
      });
  AutoJoinThread add_thread3(std::thread(std::move(task3), add_result, add_result2));
}

int Foo::Get(){
  return value_;
}

