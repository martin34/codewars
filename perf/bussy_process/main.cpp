#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

class WaitCounter {
public:
  void Increase() {
    auto old_value = counter_;
    ++counter_;
    if (old_value > counter_) {
      HandleOverflow();
    }
  }
  void HandleOverflow() { std::cout << "WaitCounter overflow" << '\n'; }

  std::uint64_t GetValue() { return counter_; }

private:
  std::uint64_t counter_{0};
};

void PrintA() { std::cout << "A" << '\n'; }

void BusyWaitFor(std::chrono::seconds seconds) {
  auto start_time = std::chrono::system_clock::now();
  WaitCounter wait_counter;
  while (start_time + seconds > std::chrono::system_clock::now()) {
    wait_counter.Increase();
  }
  std::cout << "Wait counter value: " << wait_counter.GetValue() << '\n';
}

int main(int, char **) {
  while (true) {
    PrintA();
    BusyWaitFor(1s);
  }
}