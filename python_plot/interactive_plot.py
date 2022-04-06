# -*- coding: utf-8 -*-
from dash import Dash, dcc, html
from dash.dependencies import Input, Output, State
from plotly.subplots import make_subplots
import plotly.graph_objects as go
import numpy as np
import math
import re

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

app = Dash(__name__, external_stylesheets=external_stylesheets)

@app.callback(Output("graph", "figure"), 
    Input("submit-button-state", "n_clicks"), 
    State("input-file", 'value'),
    State('pattern', 'value'))
def update_graph_live(n_clicks, input_file, pattern):
    regex_pattern = re.compile(pattern)
    parsed_data = {}
    with open(input_file) as f:
        for line in f:
            match = regex_pattern.match(line)
            if match:
                if match[1] in parsed_data:
                    parsed_data[match[1]].append(int(match[2]))
                else:
                    parsed_data[match[1]] = [int(match[2])]

    fig = make_subplots(rows=len(parsed_data), cols=1, shared_xaxes=True)
    i = 0
    for key,value in parsed_data.items():
        fig.add_trace(go.Scatter(x=list(range(len(value))), y=value, name=key, mode="lines+markers"), row=i+1, col=1)
        i += 1

    widget = go.FigureWidget(fig)
    return widget


app.layout = html.Div([
    dcc.Input(id='input-file', type='text', value="other_file.txt"),
    dcc.Input(id='pattern', type='text', value="(\w):(\d)"),
    html.Button(id='submit-button-state', n_clicks=0, children='Submit'),
    html.Div(id='output-state'),
    dcc.Graph(id="graph", animate=True),
])


@app.callback(Output('output-state', 'children'),
              Input("submit-button-state", "n_clicks"), 
              State('input-file', 'value'),
              State('pattern', 'value'))
def update_output(n_clicks, input_file, pattern):
    return u'''
        The Button has been pressed {} times,
        the used file is: "{}",
        the used pattern is: "{}"
    '''.format(n_clicks, input_file, pattern)


if __name__ == '__main__':
    app.run_server(debug=True)
