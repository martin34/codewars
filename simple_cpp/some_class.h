#pragma once

constexpr std::int32_t kParent = 3;

class Parent {
public:
  std::int32_t ReturnANumberFoo() { return ReturnANumber(); }

  virtual std::int32_t ReturnANumber() { return kParent; }

  virtual ~Parent() = default;
};

constexpr std::int32_t kChild = 2;

class Child : public Parent {
public:
  std::int32_t ReturnANumber() override { return kChild; }
};
