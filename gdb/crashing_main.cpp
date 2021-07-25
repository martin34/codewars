#include <chrono>
#include <thread>

void ProduceSegfault() {
  int a[1];
  a[0] = 0;
  a[1] = 3;
  std::ignore = a;
}

using namespace std::chrono_literals;

int main(int, char **) {
  std::this_thread::sleep_for(10s);
  ProduceSegfault();
}
