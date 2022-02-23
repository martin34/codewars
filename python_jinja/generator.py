from jinja2 import Environment, PackageLoader
import sys

env = Environment(
    loader=PackageLoader("generator"), # Python package --> name of this file
)

template = env.get_template("example_template.cpp.jinja")
names = []
with open(sys.argv[1], 'r') as f:
    names = [line.rstrip() for line in f]

with open(sys.argv[2], 'w') as f:
    f.write(template.render(names=names[1:], special=names[0]))
