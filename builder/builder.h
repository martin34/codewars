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

class ICreator {
public:
  virtual ~ICreator() = default;
  virtual std::unique_ptr<IPart> Create() = 0;
};
template <class T> class Creator : public ICreator {
public:
  std::unique_ptr<IPart> Create() override {
    return std::unique_ptr<T>{new T{}};
  }
};
template <class T, class F> class Creator2 : public ICreator {
public:
  Creator2(F &f) : f_(f) {}

  std::unique_ptr<IPart> Create() override {
    auto part = std::unique_ptr<T>{new T{}};
    part->Set(f_);
    return std::move(part);
  }
  F &f_;
};

class Builder {
public:
  auto Build() {
    Product product{};
    for (auto &creator : creators_) {
      product.Add(creator->Create());
    }
    return product;
  }

  template <class Part> Builder &AddPart() {
    creators_.push_back(std::unique_ptr<Creator<Part>>{new Creator<Part>{}});
    return *this;
  }
  template <class Part, class Thing> Builder &AddPart(Thing &thing) {
    creators_.push_back(std::unique_ptr<Creator2<Part, Thing>>{
        new Creator2<Part, Thing>{thing}});
    return *this;
  }
  // template <class Thing> void With(Thing &thing) {
  // create_functions_.back() = std::function<std::unique_ptr<IPart>()>{
  //     [create_function = create_functions_.back(), &thing]() {
  //       auto obj_ptr = create_function();
  //       obj_ptr->Set(thing);
  //       return obj_ptr;
  //     }};
  //   std::unique_ptr<ICreator>{new Creator2<decltype(*creators_.back()),
  //   Thing>(thing)};
  // }

private:
  std::vector<std::unique_ptr<ICreator>> creators_;
};