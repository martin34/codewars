#include <chrono>
#include <thread>

void ProduceSegfault() {
  int a[1];
  a[0] = 0;
  a[1] = 3;
}

using namespace std::chrono_literals;

int main(int argc, char **argv) {
  std::this_thread::sleep_for(10s);
  ProduceSegfault();
}
