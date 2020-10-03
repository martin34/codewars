load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "kings_table",
    srcs = [
        "fibonacci.cpp",
        "graph.cpp",
        "kings_table.cpp",
    ],
    hdrs = [
        "fibonacci.h",
        "graph.h",
        "kings_table.h",
    ],
    visibility = [":__subpackages__"],
)

cc_binary(
    name = "kings_banquet",
    srcs = ["main.cpp"],
    deps = [":kings_table"],
)
