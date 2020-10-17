#!/bin/sh
PID=$(ps -xeo pid,nice,user,args | grep '[/]main.o' | awk '{print $1}')
echo $PID
