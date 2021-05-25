load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "example",
    srcs = ["example.cpp"],
    deps = [
        "//unique_id:example",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
