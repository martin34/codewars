cc_library(
    name = "lib",
    srcs = glob(["src/**/*.cpp"]),
    hdrs = glob(["src/**/*.h"]),
)

cc_test(
    name = "tests",
    srcs = ["test/wilson_prime_spec.cpp"],
    deps = [
        ":lib",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)

cc_binary(
    name = "benchmark",
    srcs = ["test/wilson_prime_performance.cpp"],
    deps = [
        ":lib",
        "@benchmark//:benchmark_main",
    ],
)
