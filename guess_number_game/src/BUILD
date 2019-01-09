cc_binary(
    name = "hello-world",
    srcs = ["main.cpp"],
)

cc_library(
    name = "lib",
    srcs = ["guesser.cpp"],
    hdrs = ["guesser.h"],
    visibility = ["//guess_number_game/test:__pkg__"],
)
