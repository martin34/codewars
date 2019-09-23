load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "pocker_lib",
    srcs = glob(
        [
            "src/*.h",
            "src/*.cpp",
        ],
        exclude = ["src/main.cpp"],
    ),
    hdrs = glob(["include/*.h"]),
    strip_include_prefix = "include",
)

cc_binary(
    name = "pocker",
    srcs = ["src/main.cpp"],
    data = [
        "pocker.txt",
    ],
    linkopts = ["-lstdc++fs"],
    deps = [
        ":pocker_lib",
    ],
)

cc_test(
    name = "pocker_spec",
    srcs = glob([
        "test/*.cpp",
    ]),
    deps = [
        ":pocker_lib",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
