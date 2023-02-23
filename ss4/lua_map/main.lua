package.cpath = "./src/?.so;" -- set path to C library
my_lib = require("libmy_lib")

function fun(x)
    return x * x + 1
end

function main()
    local array = {1,2,3,4,5}
    my_lib.map(array, fun)

    for i,v in pairs(array) do
        print(string.format("res[%d] = %d", i, v))
    end
end

main()
