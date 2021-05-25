#pragma once

#include <cstdint>
#include <typeinfo>

std::int32_t GenerateId();

template <typename T> std::int32_t Id() {
  static std::int32_t id{GenerateId()};
  return id;
}

class ILogger {
public:
  virtual void Log(std::int32_t id) = 0;
  virtual void Log(const char *id) = 0;
  virtual ~ILogger() = default;
};

template <typename T> class Base {
public:
  Base(ILogger &logger) : logger_{&logger} {}
  virtual void Do() {
    logger_->Log(Id<T>());
    logger_->Log(typeid(T).name());
    DoImpl();
  }
  virtual ~Base() = default;

private:
  virtual void DoImpl() = 0;
  ILogger *logger_;
};

class DerivedA : public Base<DerivedA> {
public:
  DerivedA(ILogger &logger) : Base<DerivedA>(logger) {}

private:
  virtual void DoImpl() override {}
};
