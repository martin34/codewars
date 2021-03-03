def _example_rule(ctx):
    print("_example_rule impl")

    output = ctx.actions.declare_file("generated_data.txt")
    ctx.actions.run(
        executable = ctx.executable.generator,
        arguments = ["--out_path={}".format(output.path)],
        outputs = [output],
    )

    final = ctx.actions.declare_file("mapped_data.txt")
    ctx.actions.run(
        executable = ctx.executable.mapper,
        arguments = ["--out_path={}".format(final.path), "--input_path={}".format(output.path)],
        inputs = [output],
        outputs = [final],
    )

    return [
        DefaultInfo(files = depset([final])),
    ]

example_rule = rule(
    implementation = _example_rule,
    attrs = {
        "generator": attr.label(executable = True, cfg = "host", default = Label("//bazel_rules:generator")),
        "mapper": attr.label(executable = True, cfg = "host", default = Label("//bazel_rules:mapper")),
    },
)
