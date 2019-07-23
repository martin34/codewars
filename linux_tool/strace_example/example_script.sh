#!/bin/sh

#$$ gets the PID
TMPFILE=/tmp/some_file.$$ 
echo "File path: $TMPFILE" echo "Bar" > $TMPFILE 
cat $TMPFILE
