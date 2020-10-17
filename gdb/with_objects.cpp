#include <cstdlib>

class IFoo {
public:
  virtual ~IFoo() = default;
  virtual void DoFoo() = 0;
};

class Foo : public IFoo {
public:
  void DoFoo() override { ++i; }
  void Crash() { std::abort(); }

private:
  int i{0};
};

int main(int argc, char **argv) {
  Foo foo{};
  foo.DoFoo();
  IFoo &ifoo = foo;
  ifoo.DoFoo();
  foo.Crash();
}
