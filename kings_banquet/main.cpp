#include <iomanip>
#include <iostream>

#include "kings_table.h"

int main(int argc, char **argv) {
  std::ignore = argc;
  std::ignore = argv;

  for (std::uint64_t n = 2; n < 99; ++n) {
    std::cout << "n = " << std::setw(2) << n << ": ";
    KingsTable table{n};
    try {
      table.ArrangeSeating();
    } catch (std::runtime_error const &) {
      std::cout << ": no solution" << '\n';
      continue;
    }
    std::cout << '\n';

    auto const seating_arrangement = table.GetSeatingArrangement();
    for (auto const seat : seating_arrangement) {
      std::cout << std::setw(2) << seat << " ";
    }
    std::cout << '\n';
  }
  return 0;
}