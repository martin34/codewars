load("@rules_python//python:defs.bzl", "py_test")

py_library(
    name = "lib",
    srcs = [
        "lib.py",
    ],
)

py_test(
    name = "tests",
    srcs = [
        "tests.py",
    ],
    python_version = "PY3",
    deps = [":lib"],
)
