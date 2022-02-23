genrule(
    name = "example_cpp_generator",
    srcs = [
        ":generator.py",
        ":names.txt",
    ],
    outs = ["main.cpp"],
    cmd = "python3 $(location :generator.py) $(location :names.txt) $@",
)

cc_binary(
    name = "example_bin",
    srcs = [":main.cpp"],
)
