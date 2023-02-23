package.cpath = "./src/?.so;" -- set path to C library
my_lib = require("libmy_lib")


function main()
    local s = "hi,,there!"
    local res_split = my_lib.split(s, ",")
    for i,v in pairs(res_split) do
        print(string.format("res_split[%d] = %s", i, v))
    end
end

main()
