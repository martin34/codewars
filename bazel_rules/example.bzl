ExampleInfo = provider(
    "Example provider",
    fields = {
        "headers": "Just to show",
        "files": "depset of Files generated",
    },
)

def _example_rule(ctx):
    abc = []
    for dep in ctx.attr.deps:
        abc += dep[CcInfo].compilation_context.headers.to_list()

    output = ctx.actions.declare_file("generated_data.txt")
    ctx.actions.run(
        executable = ctx.executable.generator,
        arguments = ["--out_path={}".format(output.path)],
        outputs = [output],
    )

    final = ctx.actions.declare_file("mapped_data.txt")
    ctx.actions.run(
        executable = ctx.executable.mapper,
        arguments = ["--out_path={}".format(final.path), "--input_path={}".format(output.path)] + [f.path for f in abc],
        inputs = [output] + abc,
        outputs = [final],
    )

    return [
        ExampleInfo(headers = abc, files = depset([final])),
    ]

example_rule = rule(
    implementation = _example_rule,
    attrs = {
        "generator": attr.label(executable = True, cfg = "host", default = Label("//bazel_rules:generator")),
        "mapper": attr.label(executable = True, cfg = "host", default = Label("//bazel_rules:mapper")),
        "deps": attr.label_list(providers = [CcInfo]),
    },
)
