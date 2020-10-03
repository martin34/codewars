load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "spec",
    srcs = glob(["*.cpp", "*.h"]),
    deps = [
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
        "//kings_banquet:kings_table",
    ],
)