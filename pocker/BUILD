load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "pocker",
    srcs = glob(
        [
            "*.h",
            "*.cpp",
        ],
        exclude = ["main.cpp"],
    ),
    hdrs = glob(["*.h"]),
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
        "-lc++fs",
    ],
    deps = [
        ":pocker",
    ],
)
