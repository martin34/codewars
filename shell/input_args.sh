#!/bin/sh

TARGET_DIR=$1
if [ -z "$TARGET_DIR" ]
then
  echo "Missing argument directory, nothing to do"
  exit 1
fi

is_directory()
{
    if [ ! -d "$1" ]
    then
        echo "Directory $1 does not exist, end program"
        exit 1
    fi
}