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

void Foo::Calc(int value, int value2){
  std::packaged_task<int(int, int)> task(add);
  std::future<int> result = task.get_future();
  std::thread add_thread(std::move(task), value, value);

  std::packaged_task<int(int, int)> task2(add);
  std::future<int> result2 = task2.get_future();
  AutoJoinThread add_thread2(std::thread(std::move(task2), value2, value2));

  add_thread.join();
  add_thread2.join();

  auto add_result = result.get();
  auto add_result2 = result2.get();

  std::packaged_task<void(int, int)> task3([this](int a, int b){
      std::cerr << "Multiply thread started with a: " << a << " b: " << b << std::endl;
      std::this_thread::sleep_for(2s);
      value_ = a * b;
      });
  AutoJoinThread add_thread3(std::thread(std::move(task3), add_result, add_result2));
}

int Foo::Get(){
  return value_;
}

