package.cpath = "./src/?.so;"
my_lib = require("libmy_lib")

function main()
    local s_1 = "foo"
    local s_2 = "-bar" 
    local s_1_2 =my_lib.concat(s_1, s_2)
    print("s_1_2 = "..s_1_2)
end

main()
