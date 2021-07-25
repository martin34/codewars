#include <thread>
// #include <iostream>

void Sleep() { std::this_thread::sleep_for(std::chrono::seconds{5}); }

int main(int, char **) {
  // std::cerr << "Sleep for 5s\n";
  Sleep();
}
