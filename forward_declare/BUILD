load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "b",
    srcs = ["b.cpp"],
    hdrs = ["b.h"],
)

cc_library(
    name = "a",
    srcs = ["a.cpp"],
    hdrs = ["a.h"],
    deps = [":b"],
)

cc_test(
    name = "test",
    srcs = ["test.cpp"],
    deps = [
        ":a",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
