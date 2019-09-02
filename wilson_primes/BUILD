cc_library(
    name = "lib",
    srcs = glob(["src/**/*.cpp"]),
    hdrs = glob(["src/**/*.h"]),
)
cc_test(
    name = "tests",
    srcs = glob(["test/**/*.cpp"]) + glob(["test/**/*.h"]),
        deps = [
        ":lib",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
