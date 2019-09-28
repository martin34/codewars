load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")

cc_test(
    name = "test",
    srcs = ["wilson_prime_spec.cpp"],
    deps = [
        "//wilson_prime",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)

cc_binary(
    name = "benchmark",
    srcs = ["wilson_prime_performance.cpp"],
    deps = [
        "//wilson_prime",
        "@benchmark//:benchmark_main",
    ],
)
