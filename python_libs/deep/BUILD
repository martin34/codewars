load("@rules_python//python:defs.bzl", "py_library")

py_library(
    name = "deep",
    srcs = [
        "deep.py",
        "inner/inner.py",
    ],
    imports = ["."],
    visibility = ["//python_libs:__pkg__"],
)
