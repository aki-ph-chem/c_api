--package.path = "lib/?.lua"
array_tool = require("my_tool")

function main()
    local array = {1,2,3,4}

    local sum_array = array_tool.sum(array)
    print("sum_array = "..sum_array)

    local prod_array = array_tool.prod(array)
    print("prod_array = "..prod_array)
end

main()
