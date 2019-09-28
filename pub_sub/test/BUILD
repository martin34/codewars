load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test",
    srcs = glob(["*.cpp"]) + glob(["*.h"]),
    deps = [
        "//pub_sub",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
