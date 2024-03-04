load("//bazel_rules:example.bzl", "ExampleInfo")

def _other_rule(ctx):
    output_file = ctx.actions.declare_file("{}.txt".format(ctx.label.name))
    all_headers = []
    for foo in ctx.attr.example_results:
        all_headers += [header.path for header in foo[ExampleInfo].headers]

    ctx.actions.run(
        executable = ctx.executable.generator,
        arguments = ["--out_path={}".format(output_file.path)] + all_headers,
        outputs = [output_file],
    )
    return [
        DefaultInfo(files = depset([output_file])),
    ]

other_rule = rule(
    implementation = _other_rule,
    attrs = {
        "generator": attr.label(executable = True, cfg = "host", default = Label("//bazel_rules:other")),
        "example_results": attr.label_list(providers = [ExampleInfo]),
    },
)
