#include <iostream>
/* #include <thread> */
/* #include <chrono> */

/* using namespace std::chrono_literals; */

int main(void) {
  /* std::this_thread::sleep_for(1s); */
  int foo{0};
  for (int i{0}; i < 1000; ++i) {
    foo += i;
  }
  std::cout << "Result: " << foo << '\n';

  return 0;
}
