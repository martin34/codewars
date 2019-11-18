load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "main",
    srcs = ["main.py"],
    deps = [
        "//python_libs/deep",
        "//python_libs/module_a",
        "//python_libs/module_b",
        "//python_libs/module_d",
        "//python_libs/some_name_not_matching_file_name",
        "//python_libs_other",
    ],
)
