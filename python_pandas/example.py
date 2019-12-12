import pandas as pd
import matplotlib.pyplot as plt
from filter_function import filter_number

# Sources:
# https://pandas.pydata.org/pandas-docs/stable/getting_started/10min.html
# https://pandas.pydata.org/pandas-docs/stable/getting_started/basics.html
# https://pandas.pydata.org/pandas-docs/stable/user_guide/visualization.html

df = pd.read_csv('example_data.csv')
print(df.tail())

df['count'] = df['Message'].apply(lambda content: filter_number(content))
print(df.tail())

print("\nStatistics:")
print(df['count'].describe())

ax = df.plot.scatter(x='Time', y='count', color='green')
df.plot.scatter(x='Time', y='Foo', ax=ax)

df['Context'].value_counts().plot(kind='bar')
plt.show()