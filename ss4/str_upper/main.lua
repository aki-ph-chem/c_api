package.cpath = "./src/?.so;" -- set path to C library
my_lib = require("libmy_lib")

function main()
    local s = "hoo bar fuga"
    local s_upper = my_lib.to_upper(s)
    print("s_upper = "..s_upper)
end

main()
