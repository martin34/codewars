#include <benchmark/benchmark.h>
#include <iostream>
#include <random>

#include "wilson_prime/wilson_prime.h"

static void BM_IsPrime(benchmark::State &state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    auto v = state.range(0);
    if (v >= 0) {
      v2::IsPrime(static_cast<std::uint32_t>(v));
    } else {
      throw std::logic_error("Invalid conversion");
    }
  }
}
// Register the function as a benchmark
// BENCHMARK(BM_IsPrime)->RangeMultiplier(2)->Range(2, 1'000'000'000);

static void CustomArguments(benchmark::internal::Benchmark *b) {
  std::uint32_t seed{15U};
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dis(2, 1'000'000'000);
  for (std::int32_t i = 0; i < 100; ++i) {
    auto arg = dis(gen);
    b->Args({arg});
  }
}
BENCHMARK(BM_IsPrime)->Apply(CustomArguments);

// Run the benchmark
BENCHMARK_MAIN();
