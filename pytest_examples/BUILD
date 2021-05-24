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
    deps = [":lib"],
    python_version = "PY3",
)
