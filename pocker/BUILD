load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "report",
    hdrs = ["report.h"],
    visibility = [":__subpackages__"],
)

cc_library(
    name = "pocker",
    srcs = glob(
        [
            "*.h",
            "*.cpp",
        ],
        exclude = ["main.cpp"],
    ),
    hdrs = glob(
        ["*.h"],
        exclude = ["report.h"],
    ),
    visibility = [":__subpackages__"],
    deps = [
        "//utils/string",
    ],
)

cc_binary(
    name = "pocker_bin",
    srcs = ["main.cpp"],
    data = [
        "pocker.txt",
    ],
    linkopts = [
        "-lstdc++fs",
    ],
    deps = [
        ":pocker",
    ] + select({
        "//:v1": ["//pocker/v1:report"],
        "//conditions:default": ["//pocker/default:report"],
    }),
)
