load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test",
    srcs = ["builder_spec.cpp"],
    deps = [
        "//builder",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
