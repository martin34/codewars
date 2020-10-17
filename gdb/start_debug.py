#!/usr/bin/python3

import subprocess
import time

cmd = ["gdb", "-batch", "-ex", "run", "-ex", "bt", "-ex", "generate-core-file", "-ex", "quit", "main.o"]
print(cmd)

process = subprocess.Popen(cmd)
print(f"Child process id: {process.pid}")

time.sleep(1)
pid_process = subprocess.run("./get_pid.sh", capture_output=True)
print(f"Cpp program pid: {pid_process.stdout}")
process.wait()
