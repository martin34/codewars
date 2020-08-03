#!/bin/sh

TARGET_DIR=$1
if [ -z "$TARGET_DIR" ]
then
  echo "Missing argument directory, nothing to do"
  exit 1
fi

echo "Wait for new file in $TARGET_DIR"
# sudo apt-get install inotify-tools
inotifywait -e attrib $TARGET_DIR
echo "New file was created"
