cc_library(
    name = "pocker_lib",
    hdrs = glob(["include/*.h"]),
    srcs = glob([
        "src/*.h",
        "src/*.cpp",
    ]),
    strip_include_prefix = "include",
)

cc_test(
    name = "pocker_spec",
    srcs = [
        "test/pocker_spec.cpp",
    ],
    deps = [
        ":pocker_lib",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
