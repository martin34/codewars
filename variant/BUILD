load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "state_machine",
    srcs = glob(
        [
            "*.h",
            "*.cpp",
        ],
    ),
    hdrs = glob(["*.h"]),
    visibility = [":__subpackages__"],
)
