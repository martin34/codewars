load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "pocker_spec",
    srcs = glob([
        "*.cpp",
    ]),
    deps = [
        "//pocker",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
