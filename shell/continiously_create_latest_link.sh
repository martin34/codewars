#!/bin/sh

# Get path to this script to import other scripts
SCRIPT_DIR=$(dirname $(readlink -f $0))

. $SCRIPT_DIR/input_args.sh
. $SCRIPT_DIR/wait_for_new_file.sh
. $SCRIPT_DIR/create_latest_link.sh

set_TARGET_DIR_from_input $1

is_directory $TARGET_DIR
create_latest_link_to_file_in $TARGET_DIR
while true; do
  wait_for_new_file_in $TARGET_DIR
  is_directory $TARGET_DIR
  create_latest_link_to_file_in $TARGET_DIR
done
