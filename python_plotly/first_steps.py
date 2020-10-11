#!/usr/bin/python3

import numpy as np
import math
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import pandas as pd
import random


def create_animal(index):
    return random.choice(seq=['cat', 'dog', 'pig'])


def main():
    x_values = np.arange(0.0, 2 * math.pi, 0.1)
    df = pd.DataFrame(data={"x": x_values})
    df["sin"] = np.sin(df["x"])
    df["cos"] = np.cos(df["x"])
    df["animal"]=df["x"].apply(create_animal)

    fig = make_subplots(rows=3, cols=1, shared_xaxes=True)
    fig.add_trace(go.Scatter(x=df["x"], y=df["sin"], mode="lines+markers"), row=1, col=1)
    fig.add_trace(go.Scatter(x=df["x"], y=df["cos"], mode="lines+markers"), row=2, col=1)
    fig.add_trace(go.Scatter(x=df["x"], y=df["animal"], mode="markers"), row=3, col=1)
    fig.show()


if __name__ == "__main__":
    main()
