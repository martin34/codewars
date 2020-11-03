#!/usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("out.csv", index_col=0)
print(df.tail())
df.plot.scatter(x="x", y="y")
plt.show()
