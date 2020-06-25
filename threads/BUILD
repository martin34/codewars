load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "threads",
    srcs = ["simple_threading.cpp"],
    hdrs = [
        "auto_join_thread.h",
        "simple_threading.h",
    ],
    visibility = ["//threads/test:__pkg__"],
)

cc_binary(
    name = "user_input",
    srcs = ["user_input.cpp"],
    visibility = ["//threads/test:__pkg__"],
    deps = [
        "@boost//:program_options",
    ],
    linkopts = ["-lpthread"],
)
