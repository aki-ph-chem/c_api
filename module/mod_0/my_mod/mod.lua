local m = {}

function m.greet(name)
    print(string.format("Hello %s!",name))
end

function m.my_add(x, y)
   return x + y
end

return m;
