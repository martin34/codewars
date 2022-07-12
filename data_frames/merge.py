import pandas as pd

first = pd.DataFrame.from_dict({'time': [0, 3, 5, 7], 'x': [10., 11., 12., 13.]})
print(first.tail())

second = pd.DataFrame.from_dict({'time': [2, 4, 6, 8], 'y': [100., 101., 102., 103.]})
print(second.tail())

inner_merge = first.merge(second)
print(inner_merge.tail())

left_merge = first.merge(second, how='left')
print(left_merge.tail())

outer_merge = first.merge(second, how='outer').sort_values(by="time").interpolate()
outer_merge['x[-1]'] = outer_merge['x'].shift(1)
outer_merge['y[-1]'] = outer_merge['y'].shift(1)
outer_merge['distance'] = ((outer_merge['x']-outer_merge['x[-1]'])**(2) + (outer_merge['y']-outer_merge['y[-1]'])**(2))**(1./2.)
print(outer_merge.tail())
