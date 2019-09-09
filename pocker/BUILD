cc_library(
    name = "pocker_lib",
    srcs = glob([
        "src/*.h",
        "src/*.cpp",
    ]),
)

cc_test(
    name = "pocker_spec",
    srcs = [
        "test/pocker_spec.cpp",
    ],
    deps = [
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
