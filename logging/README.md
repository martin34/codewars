## Log some data in an multi threaded and multi process evironment

This is not about providing a perfect logging framework. The goal is to train my usage of threads and to experiment with ways to share resources between processes and threads.

### Good to know

Restrict resources of processes:
https://scoutapm.com/blog/restricting-process-cpu-usage-using-nice-cpulimit-and-cgroups

CPU:
* nice: niceness of a process is by default 0. It can be a value between -20 (high prio) and 19 (low prio). The scheduler will give it more or less cpu time, depending on the value. Use renice to change the value.
* stress-ng: tool to stress test a computer system

Sanbox /dev 
`bwrap --dev-bind / / --dev /dev bash`
