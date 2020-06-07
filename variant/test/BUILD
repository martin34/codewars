load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test",
    srcs = glob(["*.cpp"]),
    deps = [
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
        "//variant:state_machine"
    ],
)