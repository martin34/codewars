## Performance comparison python vs shell tools

```shell
# Create big file
{repeat 1000000 echo 'some random data x: 1.0 y: 2.13'} > big_data.txt
time (sh data2csv.sh)
time (python3 data2csv.py > out.csv)
```
Shell version takes about 5 seconds.
Python version less than 1 second.
