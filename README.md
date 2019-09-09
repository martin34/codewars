# My cpp Code Katas and usefull resources
## Good to remember
* GMock example: https://github.com/davidstutz/googletest
* https://www.fluentcpp.com

## Debug with gdb and bazel
1. Build with debug symbols: bazel build ... --compilation_mode=dbg -s
2. start gdb
3. list, run, break, unitl, step, next, finish, continue, print, ... (https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)

## Benchmark
* https://github.com/google/benchmark
* Example: `bazel run //wilson_primes:benchmark`

## Compiler explorer
https://godbolt.org/
