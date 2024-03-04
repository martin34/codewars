load("example.bzl", "example_rule")
load("other.bzl", "other_rule")
load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "generator",
    srcs = ["generator.py"],
)

py_binary(
    name = "mapper",
    srcs = ["mapper.py"],
)

py_binary(
    name = "other",
    srcs = ["other.py"],
)

example_rule(
    name = "foo",
    deps = [
        "//builder",
        "//csv",
    ],
)

other_rule(
    name = "other_rule_instance",
    example_results = [
        ":foo",
    ],
)
