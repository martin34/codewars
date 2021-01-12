module DataStuff
export say_hello
export parse_number

say_hello() = println("Hello!")

function parse_number(text)
    pattern=r"Hello world ([0-9]*)"
    m = match(pattern, text)
    parse(Int, m.captures[1]) # return
end

# your other definitions here

end