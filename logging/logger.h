#pragma once

#include <exception>
#include <string>

namespace logging {

class Logger {
public:
  // Caller needs to hold reference until the end of life of the executable
  // Especially for testing this is a problem
  // --> Clean up in tests, use a shared_ptr
  static void SetLogger(Logger &logger) { logger_ = &logger; }
  // Can this be done via a contract, that SetLogger needs to be called before?
  static Logger &GetLogger() {
    if (logger_ == nullptr) {
      throw std::runtime_error("Concrete Logger not set before usage");
    }
    return *logger_;
  }
  virtual void LogError(std::string const &message) = 0;

private:
  static Logger *logger_;
};

Logger *Logger::logger_ = nullptr;

} // namespace logging