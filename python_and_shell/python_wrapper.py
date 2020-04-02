#!/usr/bin/python3

import subprocess

cmd = ["./longrunning_shell.sh"]


def execute_blocking():
    print("Execute script blocking")
    process = subprocess.run(cmd, stdout=subprocess.PIPE)
    print("stdout of shell script: {}".format(process))


def execute_non_blocking():
    print("Execute non blocking")
    with subprocess.Popen(cmd, stdout=subprocess.PIPE, universal_newlines=True) as process:
        return_code = None
        while return_code is None:
            print(
                "Read from stdout: {}".format(process.stdout.readline())
            )  # Be careful to use readline and not readlines
            return_code = process.poll()
        print("Return code {}".format(return_code))


def main():
    execute_blocking()
    execute_non_blocking()


if __name__ == "__main__":
    main()
