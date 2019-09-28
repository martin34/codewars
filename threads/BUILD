load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "threads",
    srcs = ["simple_threading.cpp"],
    hdrs = [
        "auto_join_thread.h",
        "simple_threading.h",
    ],
    visibility = ["//threads/test:__pkg__"],
)
