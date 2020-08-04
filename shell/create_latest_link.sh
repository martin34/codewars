#!/bin/sh

. ./input_args.sh

FILE=$(ls -rt $TARGET_DIR | tail -n1)
if [ -z "$FILE" ]
then
  echo "Directory is empty, nothing to do"
  exit 2
fi

echo "Create symlink called latest in $1 to $FILE"
# ln -s $TARGET_DIR/`ls -rt $TARGET_DIR | tail -n1` latest
ln -sf $TARGET_DIR/$FILE latest
