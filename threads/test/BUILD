load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "tests",
    srcs = [
        "shared_resource_spec.cpp",
        "simple_threading_spec.cpp",
    ],
    deps = [
        "//threads",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)

cc_test(
    name = "user_input_tests",
    srcs = [
        "user_input_spec.cpp",
    ],
    data = [
        "//threads:user_input",
    ],
    deps = [
        "//threads",
        "@boost//:process",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
