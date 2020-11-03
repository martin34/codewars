#!/usr/bin/python3

import re

with open("data.txt") as f:
    pattern = re.compile("some random data x: (\d*\.\d*) y: (\d*\.\d*)")
    print("index,x,y")
    i = 0
    for line in f:
        match = pattern.match(line)
        if match:
            print(f"{i},{match[1]},{match[2]}")
            i += 1
