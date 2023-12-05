#include <iostream>
#include <vector>

class Interface {
public:
  ~Interface() = default;
  virtual void DoSomething() = 0;
};

class Base : public Interface
{
public:
  void DoSomething() override {
    std::cout << "Base does something with b = " << b << std::endl;
    ++b;
  }
private:
  int b{13};
};

class Child : public Base
{
public:
  void DoSomething() override {
    std::cout << "Child does something with c = " << c << std::endl;
    c += 2;
  }
private:
  int c{14};
};

int main(int, char **) {
    Base b{};
    b.DoSomething();
    Child c{};
    c.DoSomething();
    Interface& ci{c};
    std::vector<Interface*> things{&b, &c};
    std::for_each(things.begin(), things.end(), [](auto i){i->DoSomething();});
    ci.DoSomething();
    Child oc{};
    oc.DoSomething();
}
