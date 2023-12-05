load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "crashing_bin",
    srcs = ["crashing_main.cpp"],
)

cc_binary(
    name = "waiting_bin",
    srcs = ["main.cpp"],
)

sh_binary(
    name = "run",
    srcs = ["run.sh"],
    data = [
        ":crashing_bin",
        ":waiting_bin",
    ],
)

cc_binary(
    name = "inheritance",
    srcs = ["inheritance.cpp"],
)
