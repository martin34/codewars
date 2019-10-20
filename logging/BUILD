load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "logging",
    srcs = [],
    hdrs = ["logger.h"],
    visibility = [":__subpackages__"],
)

cc_binary(
    name = "example",
    srcs = ["example_app.cpp"],
    linkopts = ["-lpthread"],
)
