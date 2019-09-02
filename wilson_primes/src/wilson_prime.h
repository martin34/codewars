#pragma once

#include <cstdint>

inline bool IsDivisibleBy(std::uint64_t dividend, std::uint64_t divisor) {
  return dividend % divisor;
}

bool IsPrime(std::uint32_t n);

// P is a prime number
//   ((P-1)! + 1) mod (P * P) = 0
bool IsWilsonPrime(std::uint32_t n);