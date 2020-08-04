#!/bin/sh

# Get path to this script to import other scripts
SCRIPT_DIR=$(dirname $(readlink -f $0))

. $SCRIPT_DIR/input_args.sh

is_directory $TARGET_DIR
./create_latest_link.sh $TARGET_DIR
while true; do
  ./wait_for_new_file.sh $TARGET_DIR
  is_directory $TARGET_DIR
  ./create_latest_link.sh $TARGET_DIR
done
