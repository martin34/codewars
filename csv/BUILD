load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "csv",
    srcs = glob(
        ["*.cpp"],
        exclude = ["main.cpp"],
    ),
    hdrs = glob(["*.h"]),
    linkopts = [
        "-lstdc++fs",
    ],
    visibility = ["//csv/test:__pkg__"],
    deps = ["//utils/string"],
)

cc_binary(
    name = "csv_bin",
    srcs = ["main.cpp"],
    deps = [
        ":csv",
    ],
)
