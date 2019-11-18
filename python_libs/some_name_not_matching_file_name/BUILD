load("@rules_python//python:defs.bzl", "py_library")

py_library(
    name = "some_name_not_matching_file_name",
    srcs = [
        "module_c.py",
    ],
    imports = ["."],
    visibility = ["//python_libs:__pkg__"],
)
