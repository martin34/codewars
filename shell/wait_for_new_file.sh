#!/bin/sh

SCRIPT_DIR=$(dirname $(readlink -f $0))
. $SCRIPT_DIR/input_args.sh

wait_for_new_file_in()
{
  set_TARGET_DIR_from_input $1
  echo "Wait for new file in $TARGET_DIR"
  # sudo apt-get install inotify-tools
  inotifywait -e attrib $TARGET_DIR
  echo "New file was created"
  return 0
}