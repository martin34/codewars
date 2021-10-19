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
```shell
bazel run --conifg=asan //bad_code:out_of_bound -c dbg
bazel run --conifg=usan //bad_code:out_of_bound -c dbg
bazel run --config=asan //bad_code:use_after_freed -c dbg
bazel run --config=usan //bad_code:use_after_freed -c dbg
```

## Analyse bazel behavior

e. g. find reason for not using cache
```shell
bazel build //... --explain=1.log --verbose_explanations
bazel build //... --execution_log_json_file=/tmp/foo.json
```

## Search for change in all branches

```shell
git branch | xargs -I% git --no-pager log -1 -p %
```

## Coredumps 

```shell
ulimit -c unlimited => Tell bash to generate a core dump of unlimited size, when app crashes
Execute the app
Build binary with debug symbols (--copt -g)
gdb <executable> -c core
```

## Split debug informations

[GDB: Separate-Debug-Files](https://sourceware.org/gdb/onlinedocs/gdb/Separate-Debug-Files.html#Separate-Debug-Files)

```shell
cp bin bin.debug
Optional: sudo strip --only-keep-debug bin.debug
sudo strip --strip-debug ./bin

sudo objcopy --add-gnu-debuglink bin.debug bin
gdb bin -c core
# or
readelf -n libpocker.so # Get Build ID
mkdir -p /tmp/debug/.build-id/nn/nnnnnnnnn.debug # nn == first 2 caracters of Build ID; nnnnnnnnn == rest of Build ID
gdb bin -c core
$ set debug-file-directory /tmp/debug

```

## Property based testing
 
[Introduction](https://medium.com/criteo-labs/introduction-to-property-based-testing-f5236229d237)

* C++: https://github.com/emil-e/rapidcheck
* Python: https://hypothesis.readthedocs.io/en/latest/

## Run bazel in background 
```shell
bazel --io_nice_level=7 build //... # Set low priority via startup optioin
```

## Traffic shaping
