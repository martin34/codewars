load("@rules_rust//rust:defs.bzl", "rust_binary", "rust_library")

rust_library(
    name = "pocker_lib",
    srcs = ["hand.rs"],
    visibility = [":__subpackages__"],
)

rust_binary(
    name = "main",
    srcs = ["main.rs"],
    deps = [
        ":pocker_lib",
    ],
)
