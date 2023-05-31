def greeting_generator(name, names_file):
    native.genrule(
        name = name,
        outs = ["main.cpp"],
        srcs = [names_file],
        cmd = "python3 $(location //python_jinja:generator) $< $@",
        tools = ["//python_jinja:generator"],
    )
    native.cc_binary(
        name = "{}_bin".format(name),
        srcs = [":main.cpp"],
    )
