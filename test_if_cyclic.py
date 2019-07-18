#!/usr/bin/python

import sys

if len(sys.argv) < 3:
    exit()


end = int(sys.argv[1])
g = int(sys.argv[2])

potential_elements = []

for i in range(1, end, 1):
    potential_elements.append(g**i%end)

print("Number of unique elements: {}".format(len(set(potential_elements))))
