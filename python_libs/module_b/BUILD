load("@rules_python//python:defs.bzl", "py_library")

py_library(
    name = "module_b",
    srcs = ["some_name_not_mathing_folder_name.py"],
    imports = ["."],
    visibility = ["//python_libs:__pkg__"],
)
