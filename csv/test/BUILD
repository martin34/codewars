load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "tests",
    srcs = glob(["*.cpp"]) + glob(["*.h"]),
    data = [
        ":data/empty_file.csv",
        ":data/short_file.csv",
    ],
    deps = [
        "//csv",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
