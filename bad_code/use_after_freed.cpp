#include <iostream>

class Foo {
public:
  Foo() = default;
  Foo(int v) : a(v) {}
  int *GetBar() { return &a; }

private:
  int a{9};
};

// Does not even build because of: -Werror=return-local-addr
/* int& GetInvalidRef(){
   int a{2};
   return a;
} */

int main() {
  Foo c{1};
  int *a = c.GetBar();
  {
    Foo b;
    a = b.GetBar();
  }
  std::cout << *a << '\n';
  std::cout << *c.GetBar() << '\n';
}
