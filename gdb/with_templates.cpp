#include <cstdio>
#include <cstdlib>

template <typename T> T add(T lhs, T rhs) { return lhs + rhs; }

template int add<int>(int lhs, int rhs);

int main(int argc, char **argv) {
  int a{3};
  auto b = add(a, a);
  auto c = add(3., 4.);
  printf("Result: %d %f\n", b, c);
  std::abort();
}
