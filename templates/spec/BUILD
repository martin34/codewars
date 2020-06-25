load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "spec",
    srcs = glob(["*.cpp"]),
    deps = [
        "//templates",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
