#include <chrono>
#include <iostream>
#include <thread>

// http://man7.org/linux/man-pages/man7/sem_overview.7.html
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

using namespace std::chrono_literals;

void verbose_wait(std::chrono::seconds const &duration) {
  auto number_of_seconds = duration.count();
  for (; number_of_seconds > 0; --number_of_seconds) {
    std::this_thread::sleep_for(1s);
    std::cerr << "Seconds left to wait: " << number_of_seconds << '\n';
  }
}

class ProcessMutex {
public:
  ProcessMutex() {
    auto permission_bits = 0644;
    auto initial_value = 1;
    mutex_ =
        sem_open("/ExampleFooMutex", O_CREAT, permission_bits, initial_value);

    std::cerr << "Wait until semaphore value is greater than zero" << '\n';
    std::cerr << "Current semaphore value: " << GetValue() << '\n';
    sem_wait(mutex_);
  }

  ~ProcessMutex() { sem_post(mutex_); }

private:
  int GetValue() {

    int value{};
    sem_getvalue(mutex_, &value);
    return value;
  }
  sem_t *mutex_;
};

int main(int argc, char **argv) {
  std::ignore = argc;
  std::ignore = argv;
  std::cout << "Start app" << '\n';

  ProcessMutex mutex;
  verbose_wait(10s);
}