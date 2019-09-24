load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "string",
    srcs = ["split.cpp"],
    hdrs = ["split.h"],
    visibility = [
        ":__subpackages__",
        "//csv:__pkg__",
        "//pocker:__subpackages__",
    ],
)
