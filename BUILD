# Play with config settings
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")

string_flag(
    name = "variation",
    build_setting_default = "",
)

config_setting(
    name = "v1",
    flag_values = {
        ":variation": "v1",
    },
)
