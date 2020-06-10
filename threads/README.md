# Threads

## Find race conditions in tests

```console
# Produce stress on system e. g.:
sudo stress-ng --cpu 8 --timeout 60 --metrics-brief
# Run tests with low scheduling priority multiple times e. g.:
bazel test //threads/... --runs_per_test=20 --run_under='nice -n 19'
# Observe processes
ps -eo pid,nice,user,args | grep threads/test
```

For the test fixed in this commit this produced up to 14 failures out of 20 runs instead of 4 failures out of 20.

Resources:
* [stress-ng](https://www.tecmint.com/linux-cpu-load-stress-test-with-stress-ng-tool/2/)
* [nice](http://www.gnu.org/software/coreutils/manual/html_node/nice-invocation.html#nice-invocation)