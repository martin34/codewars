load("@rules_rust//rust:defs.bzl", "rust_test")

rust_test(
    name = "spec",
    srcs = ["spec.rs"],
    deps = [
        "//rust/pocker:pocker_lib",
        "@crate_index//:parameterized",
    ],
)
