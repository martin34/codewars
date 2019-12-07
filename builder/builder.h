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
  void Do() {
    for (auto &part : parts_) {
      part->Do();
    }
  }

  void Add(std::unique_ptr<IPart> part) { parts_.push_back(std::move(part)); }
  std::vector<std::unique_ptr<IPart>> &GetParts() { return parts_; }

private:
  std::vector<std::unique_ptr<IPart>> parts_{};
};

class Builder {
public:
  auto Build() {
    auto create_function = create_functions_.at(0);
    auto part_ptr = create_function();
    Product product{};
    for (auto create_function : create_functions_) {
      product.Add(create_function());
    }
    return product;
  }

  template <class Part> void AddPart() {
    std::function<std::unique_ptr<IPart>()> create_function{
        []() { return std::unique_ptr<IPart>{new Part{}}; }};
    create_functions_.push_back(create_function);
  }

private:
  std::vector<std::function<std::unique_ptr<IPart>()>> create_functions_{};
};