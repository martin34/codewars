load("@rules_python//python:defs.bzl", "py_library")

py_library(
    name = "module_d",
    srcs = [
        "module_d.py",
        "some_name_not_mathing_folder_name2.py",
    ],
    imports = ["."],
    visibility = ["//python_libs:__pkg__"],
)
