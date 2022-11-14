load("//python_jinja:generator.bzl", "greeting_generator")

py_binary(
    name = "generator",
    srcs = ["generator.py"],
    data = ["//python_jinja/templates"],
    visibility = ["//python_jinja:__subpackages__"],
)

greeting_generator(
    name = "generate_greetings",
    names_file = "names.txt",
)

cc_binary(
    name = "bin",
    srcs = [":main.cpp"],
)
