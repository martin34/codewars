load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test",
    srcs = [
        "some_class_spec.cpp",
    ],
    deps = [
        "//simple_cpp",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
