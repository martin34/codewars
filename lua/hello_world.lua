#!/usr/bin/lua

prefix = "Called: "
if arg[1] then
    print(prefix .. arg[0] .. " " .. arg[1])
else
    print(prefix .. arg[0])
end

print("Hello world")

function foo(n)
    local result = n == 1
    g_result = n
    if result then
        return "One"
    else
        return "Something else"
    end
end

print("enter a number:")
-- a = io.read("*number")        -- read a number
print(foo(3))
print("g_result: " .. g_result)
print(2*5)
print(2^5)

bar = {}
bar.a = 3
bar.b = "barbar"

local inspect = require('inspect')
print(inspect(bar))
