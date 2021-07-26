load("@rules_rust//rust:defs.bzl", "rust_binary", "rust_library")

rust_library(
    name = "person",
    srcs = ["person.rs"],
    visibility = [":__subpackages__"],
)

rust_binary(
    name = "hello_world",
    srcs = ["hello_world.rs"],
    deps = [":person"],
)
