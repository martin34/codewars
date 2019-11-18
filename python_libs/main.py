#!/usr/bin/python3

# Simple case
from module_a import hello_module_a

# File name is important, not folder name
from some_name_not_mathing_folder_name import hello_module_b
from module_b.some_name_not_mathing_folder_name import good_by_module_b
from module_c import hello_module_c

# More than one module in one library
from module_d import hello_module_d
from some_name_not_mathing_folder_name2 import hello_module_d2

# Deeper module structure in one library
from deep import deep_function
from inner.inner import inner_function

# If libray name and file name are different
from python_libs_other.foo_bar import foo_bar
from foo_bar import something_else

def main():
    print("Hello World")
    print(hello_module_a())
    print(hello_module_b())
    print(good_by_module_b())
    print(hello_module_c())
    print(hello_module_d())
    print(hello_module_d2())
    print(deep_function())
    print(inner_function())
    print(foo_bar())
    print(something_else())

if __name__== "__main__":
  main()