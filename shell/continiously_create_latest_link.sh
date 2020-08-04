#!/bin/sh

. ./input_args.sh

is_directory $TARGET_DIR
./create_latest_link.sh $TARGET_DIR
while true; do
  ./wait_for_new_file.sh $TARGET_DIR
  is_directory $TARGET_DIR
  ./create_latest_link.sh $TARGET_DIR
done
