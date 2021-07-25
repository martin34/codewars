#!/bin/sh

TMPFILE=/tmp/output.$$

g++ main.cpp -o main

strace -o $TMPFILE ./main

rm main

echo "Trace saved to file: $TMPFILE"
