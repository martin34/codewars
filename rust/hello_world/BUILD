load("@rules_rust//rust:defs.bzl", "rust_binary", "rust_library")

cc_library(
    name = "utils",
    srcs = ["utils.cpp"],
    hdrs = ["utils.h"],
)

rust_library(
    name = "person",
    srcs = ["person.rs"],
    visibility = [":__subpackages__"],
)

rust_binary(
    name = "hello_world",
    srcs = ["hello_world.rs"],
    deps = [
        ":person",
        ":utils",
    ],
)
