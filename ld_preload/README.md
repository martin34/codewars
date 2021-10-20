# Redefine symbols of standard libraries

[what-is-the-ld-preload-trick](https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick)

Check needed shared libraries with `readelf -d bazel-bin/ld_preload/throw`

```
bazel build //ld_preload:throw
bazel build //ld_preload:libthrow

./bazel-bin/ld_preload/throw
> terminate called after throwing an instance of 'std::runtime_error'
>   what():  FooBar
>   [1]    53453 abort (core dumped)  ./bazel-bin/ld_preload/throw

LD_PRELOAD=$PWD'/bazel-bin/ld_preload/liblibthrow.so' ./bazel-bin/ld_preload/throw
>
>  ################ DETECT A THROWN !!!!! #############
>  [1]    54528 abort (core dumped)  LD_PRELOAD=$PWD'/bazel-bin/ld_preload/liblibthrow.so'
```
