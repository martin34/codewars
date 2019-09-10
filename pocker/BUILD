cc_library(
    name = "pocker_lib",
    srcs = glob([
        "src/*.h",
        "src/*.cpp",
    ]),
    hdrs = glob(["include/*.h"]),
    strip_include_prefix = "include",
)

cc_test(
    name = "pocker_spec",
    srcs = [
        "test/card_deck_spec.cpp",
        "test/pocker_spec.cpp",
    ],
    deps = [
        ":pocker_lib",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
)
