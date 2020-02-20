# My cpp Code Katas and usefull resources
## Good to remember
* GMock example: https://github.com/davidstutz/googletest
* https://www.fluentcpp.com

## Debug with gdb and bazel
1. Build with debug symbols: `bazel build ... --compilation_mode=dbg -s`
2. `start gdb`
3. list, run, break, unitl, step, next, finish, continue, print, ... (https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)

## Benchmark
* https://github.com/google/benchmark
* Example: `bazel run //wilson_primes:benchmark`

## Compiler explorer
https://godbolt.org/

## Sanitizer options
Search for sanitize: 
https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html

Examples:
```
bazel run --conifg=asan //bad_code:out_of_bound -c dbg
bazel run --conifg=usan //bad_code:out_of_bound -c dbg
bazel run --config=asan //bad_code:use_after_freed -c dbg
bazel run --config=usan //bad_code:use_after_freed -c dbg
```

## Analyse bazel behavior
e. g. find reason for not using cache
`bazel build //... --explain=1.log --verbose_explanations`

## Search for change in all branches
git branch | xargs -I% git --no-pager log -1 -p %
