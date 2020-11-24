#!/usr/bin/python3

import numpy as np
import math
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import pandas as pd
import random
import time

import json
import dash
from dash.dependencies import Input, Output
import dash_core_components as dcc
import dash_html_components as html

external_stylesheets = ["https://codepen.io/chriddyp/pen/bWLwgP.css"]
app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
x_values = np.arange(0.0, 2 * math.pi, 0.1)
df = pd.DataFrame(data={"x": x_values})


def create_animal(index):
    return random.choice(seq=["cat", "dog", "pig"])


fig = make_subplots(rows=3, cols=1, shared_xaxes=True)
df["sin"] = np.sin(df["x"])
df["cos"] = np.cos(df["x"])
df["animal"] = df["x"].apply(create_animal)
fig.add_trace(go.Scatter(x=df["x"], y=df["sin"], mode="lines+markers"), row=1, col=1)
fig.add_trace(go.Scatter(x=df["x"], y=df["cos"], mode="lines+markers"), row=2, col=1)
fig.add_trace(go.Scatter(x=df["x"], y=df["animal"], mode="markers"), row=3, col=1)
widget = go.FigureWidget(fig)


i = 0


@app.callback(Output("hidden-div", "children"), [Input("basic-interactions", "clickData")])
def display_click_data(clickData):
    global i
    i += 1
    widget.layout.title.text = f"This is a new title number {i}"
    global df
    df = df.append({"x": 2 * math.pi + i * 0.1, "animal": "human"}, ignore_index=True)
    widget.update_traces(go.Scatter(x=df["x"], y=df["animal"], mode="markers"), row=3, col=1)
    print("callback executed")
    print(df.tail(5))
    return json.dumps(clickData, indent=2)


@app.callback(Output("basic-interactions", "figure"), [Input("interval-component", "n_intervals")])
def update_graph_live(n):
    print("Update")
    return widget


@app.callback(
    dash.dependencies.Output("dd-output-container", "children"), [dash.dependencies.Input("demo-dropdown", "value")]
)
def update_output(value):

    return 'You have selected "{}"'.format(value)


def main():
    app.layout = html.Div(
        [
            dcc.Dropdown(
                id="demo-dropdown",
                options=[
                    {"label": "sin", "value": "sin"},
                    {"label": "cos", "value": "cos"},
                    {"label": "animals", "value": "animals"},
                ],
                value=["sin", "cos", "animals"],
                multi=True,
            ),
            html.Div(id="dd-output-container"),
            dcc.Graph(id="basic-interactions", figure=widget, animate=True),
            html.Div(id="hidden-div", style={"display": "none"}),
            dcc.Interval(id="interval-component", interval=1 * 1000, n_intervals=0),  # in milliseconds
        ]
    )
    app.run_server(
        debug=True,
    )


if __name__ == "__main__":
    main()
