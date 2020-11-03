#!/bin/sh

echo index,x,y > out.csv
nl --starting-line-number=0 -w2 -s',' data.txt | sed -E 's/([0-9]*,)some random data x: ([0-9]*\.?[0-9]*) y: ([0-9]*\.[0-9]*)/\1\2,\3/g' >> out.csv
python3 plot.py
