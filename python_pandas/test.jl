using Test
using DataFrames
using StatsPlots

include("data.jl")
import .DataStuff

pattern = r"Hello world ([0-9]*)"
@test occursin(pattern, "Hello world 23")

@test DataStuff.parse_number("Hello world 23") == 23

lines = [
    "Hello world 1",
    "Hello world 2"]
@test DataStuff.parse_number.(lines) == [1, 2] # Apply function to every element

df = DataFrame(lines = lines)
@test size(df.lines)[1] == 2

df = select(df, :lines, :lines => ByRow(DataStuff.parse_number))
@test df.lines_parse_number[1] == 1
@test df.lines_parse_number[2] == 2

print(describe(df))

# Use julia -i test.jl
# Otherwise plot is not shown
@df df plot(:lines_parse_number, color = [:blue], show=true)
gui() 
