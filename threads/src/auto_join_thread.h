#ifndef THREADS_SRC_AUTOJOINTHREAD_H_
#define THREADS_SRC_AUTOJOINTHREAD_H_

#include <thread>

class AutoJoinThread {
public:
  AutoJoinThread(std::thread &&thread) : thread_(std::move(thread)) {}
  ~AutoJoinThread() {
    if (thread_.joinable()) {
      thread_.join();
    }
  }
  void join() { thread_.join(); }

private:
  std::thread thread_;
};

#endif //  THREADS_SRC_AUTOJOINTHREAD_H_
