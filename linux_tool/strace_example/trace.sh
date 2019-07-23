#!/bin/sh

TMPFILE=/tmp/output.$$

strace -o $TMPFILE ./example_script.sh

echo "Trace saved to file: $TMPFILE"
