cc_library(
    name = "lib",
    srcs = glob([
        "src/*.h",
        "src/*.cpp",
        ]),
    deps = [],
)

cc_test(
    name = "spec",
    srcs = [
        "test/some_class_spec.cpp"
        ],
    deps = [
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
        ":lib",
        ]
)
