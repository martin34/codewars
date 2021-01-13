#!/bin/sh
clang++ -L/usr/lib/llvm-7/lib -lclang -I/usr/lib/llvm-7/include/ main.cpp -o main -g
./main
