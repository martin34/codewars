load("//python_jinja:generator.bzl", "greeting_generator")

cc_binary(
    name = "bin",
    srcs = [":main.cpp"],
)

greeting_generator(
    name = "other_greetings",
    names_file = "other_names.txt",
)
