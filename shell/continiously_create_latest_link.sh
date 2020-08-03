#!/bin/sh

TARGET_DIR=$1
if [ -z "$TARGET_DIR" ]
then
  echo "Missing argument directory, nothing to do"
  exit 1
fi

while true; do
  echo "Step"
  ./wait_for_new_file.sh $TARGET_DIR
  ./create_latest_link.sh $TARGET_DIR
done
