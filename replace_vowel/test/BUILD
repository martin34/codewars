load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test",
    srcs = ["replace_vowel_spec.cpp"],
    deps = [
        "//replace_vowel",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
