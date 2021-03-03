load("example.bzl", "example_rule")
load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "generator",
    srcs = ["generator.py"],
)

py_binary(
    name = "mapper",
    srcs = ["mapper.py"],
)

example_rule(
    name = "foo",
)
