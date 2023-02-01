load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")

cc_library(
    name = "report",
    hdrs = ["report.h"],
    visibility = [":__subpackages__"],
)

# Advantage: Easy to use
# Disadvantage:
# * Cache is invalidated, when different flag is used
# * To test/build everything all variations in the configuration need to be called explicitly
cc_binary(
    name = "bin",
    srcs = ["main.cpp"],
    deps = [
        ":report",
    ] + select({
        ":v1": ["//variations/v1:report"],
        "//conditions:default": ["//variations/default:report"],
    }),
)

string_flag(
    name = "variation",
    build_setting_default = "",
)

config_setting(
    name = "v1",
    flag_values = {
        ":variation": "v1",
    },
)

# This provdes all variations.
# Advantage: All targets available e. g. just build and test all variations via //...
# Disadvantage: Using this apprach in low level library enables different uses to choose different variants.
# When these using libs are linked together this can cause trouble. For example pulling the default variation will lead to different results depending on the linking order.
# --> such variations should be used rarely and on a high level e. g. choosing the correct factory for the choosen setup.
# This could be also done at runtime. This is a viable solution for cases, where it is expensive to ship all variations (build time, dead code, big binary).
# --> for libs used in many places, there should be only one version in the dependency tree.
dependency_map = {
    "": "//variations/default:report",
    "_v1": "//variations/v1:report",
}

[
    cc_binary(
        name = "lbin{}".format(variant),
        srcs = ["main.cpp"],
        deps = [
            ":report",
            "{}".format(dependency_map[variant]),
        ],
    )
    for variant in [
        "",
        "_v1",
    ]
]
