cc_library(
    name = "lib",
    srcs = glob(["src/**/*.cpp"]),
    hdrs = glob(["src/**/*.h"]),
    linkopts = ["-lstdc++fs"],
)

exports_files(glob(["test/data/*.csv"]))

cc_test(
    name = "tests",
    srcs = glob(["test/**/*.cpp"]) + glob(["test/**/*.h"]),
    data = [
        ":test/data/empty_file.csv",
        ":test/data/short_file.csv",
    ],
    deps = [
        ":lib",
        "@googletest//:gtest_main",
        "@googletest//:gtest_sample_lib",
    ],
    # data = glob(["data/empty_file.csv"]),
)

cc_binary(
    name = "csv",
    srcs = glob(["main.cpp"]),
    deps = [
        ":lib",
    ],
)
