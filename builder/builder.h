#pragma once

#include <functional>
#include <memory>
#include <vector>

class IPart {
public:
  virtual ~IPart() = default;
  virtual void Do() = 0;
};

class Product {
public:
  Product(std::unique_ptr<IPart> part) : part_(std::move(part)) {}
  void Do() {}

private:
  std::unique_ptr<IPart> part_{};
};

class Builder {
public:
  auto Build() {
    auto create_function = create_functions_.at(0);
    auto part_ptr = create_function();
    return Product{std::move(part_ptr)};
  }

  template <class Part> void AddPart() {
    std::function<std::unique_ptr<IPart>()> create_function{
        []() { return std::unique_ptr<IPart>{new Part{}}; }};
    create_functions_.push_back(create_function);
  }

private:
  std::vector<std::function<std::unique_ptr<IPart>()>> create_functions_{};
};