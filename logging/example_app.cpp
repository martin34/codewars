#include <chrono>
#include <iostream>
#include <thread>

// http://man7.org/linux/man-pages/man7/sem_overview.7.html
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

using namespace std::chrono_literals;

// sem_t mutex;

void verbose_wait(std::chrono::seconds const &duration) {
  auto number_of_seconds = duration.count();
  for (; number_of_seconds > 0; --number_of_seconds) {
    std::this_thread::sleep_for(1s);
    std::cerr << "Seconds left to wait: " << number_of_seconds << '\n';
  }
}

int main(int argc, char **argv) {
  std::ignore = argc;
  std::ignore = argv;
  std::cout << "Start app" << '\n';
  auto permission_bits = 0644;
  auto initial_value = 1;
  auto mutex =
      sem_open("/ExampleFooMutex", O_CREAT, permission_bits, initial_value);
  int value{};
  sem_getvalue(mutex, &value);
  std::cerr << "Wait until semaphore value is greater than zero" << '\n';
  std::cerr << "Current semaphore value: " << value << '\n';
  sem_wait(mutex);
  verbose_wait(10s);
  sem_post(mutex);
}