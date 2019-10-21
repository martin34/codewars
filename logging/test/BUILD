load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")

cc_test(
    name = "test",
    srcs =
        [
            "logger_spec.cpp",
        ],
    deps = [
        "//logging",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)

# Somehow needs to be in a extra target, because otherwise this tests ends the gtest process
cc_test(
    name = "exec_binary",
    srcs =
        [
            "execute_binary_spec.cpp",
        ],
    data = [
        ":test_binary",
    ],
    deps = [
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)

cc_binary(
    name = "test_binary",
    srcs = ["test_binary.cpp"],
    copts = ["-Wno-write-strings"],
    linkopts = ["-lpthread"],
)
