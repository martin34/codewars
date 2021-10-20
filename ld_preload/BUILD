cc_binary(
    name = "throw",
    srcs = ["throw.cpp"],
    linkstatic = False,
    tags = ["manual"],
    deps = [
        ":throwing_lib",
    ],
)

cc_library(
    name = "throwing_lib",
    srcs = ["other_lib.cpp"],
    hdrs = ["other_lib.h"],
)

cc_library(
    name = "libthrow",
    srcs = ["reimplement_throw.cpp"],
)
