#include <benchmark/benchmark.h>

#include "wilson_primes/src/wilson_prime.h"

static void BM_IsPrime(benchmark::State &state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    IsPrime(state.range(0));
  }
}
// Register the function as a benchmark
BENCHMARK(BM_IsPrime)->RangeMultiplier(2)->Range(2, 1'000'000'000);
// Run the benchmark
BENCHMARK_MAIN();